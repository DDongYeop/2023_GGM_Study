// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "EnemyAnim.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include "TPSCharacterPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSCharacterPlayer::StaticClass());

	target = nullptr;
	
	me = Cast<AEnemy>(GetOwner());

	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());

	ai = Cast<AAIController>(me->GetController());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	default:
		break;
	}
}

void UEnemyFSM::OnDamageProcess()
{
	hp--;

	if (hp > 0)
	{
		mState = EEnemyState::Damage;

		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), index);
		if (anim)
			anim->PlayDamageAnim(FName(*sectionName));
	}
	else
	{
		mState = EEnemyState::Die;
		// 캡슐 비활성화
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (anim)
			anim->PlayDamageAnim(TEXT("Die"));
	}

	if (anim)
		anim->animState = mState;

	ai->StopMovement();
}

bool UEnemyFSM::GetRandomPositionNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc;
	return result;
}

void UEnemyFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		currentTime = 0;

		if (anim)
			anim->animState = mState;

		// 최초의 랜덤한 위치 값
		GetRandomPositionNavMesh(me->GetActorLocation(), 500, randomPos);
	}
}

void UEnemyFSM::MoveState()
{
	if (target == nullptr)
	{
		if (ai == nullptr)
			return;

		auto result = ai->MoveToLocation(randomPos);

		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			mState = EEnemyState::Idle;
			currentTime = 0;

			if (anim)
				anim->animState = mState;
		}
	}
	else
	{
		// 타겟의 목적지
		FVector dest = target->GetActorLocation();

		// 방향
		FVector dir = dest - me->GetActorLocation();

		auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

		// 목적지 길찾기 경로 데이터 검색
		FPathFindingQuery query;
		FAIMoveRequest req;

		req.SetAcceptanceRadius(3);
		req.SetGoalLocation(dest);

		// 길찾기를 위한 쿼리 생성
		ai->BuildPathfindingQuery(req, query);

		// 길찾기 결과 가져오기
		FPathFindingResult result = ns->FindPathSync(query);

		// 목적지까지의 길찾기 성공 여부 확인
		if (result.Result == ENavigationQueryResult::Success)
		{
			ai->MoveToLocation(dest);
		}
		else
		{
			auto re = ai->MoveToLocation(randomPos);

			if (re == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				mState = EEnemyState::Idle;
				currentTime = 0;

				if (anim)
				{
					anim->animState = mState;
				}
			}
		}

		// 타겟과 거리가 가까워 지면
		if (dir.Size() < attackRange)
		{
			ai->StopMovement();

			mState = EEnemyState::Attack;
			currentTime = attackDelayTime;

			if (anim)
			{
				anim->animState = mState;
				anim->bAttackPlay = true;
			}
		}
	}	
}

void UEnemyFSM::AttackState()
{
	currentTime += GetWorld()->GetDeltaSeconds();

	if (currentTime > attackDelayTime)
	{
		// 공격하기
		if (anim)
			anim->bAttackPlay = true;

		currentTime = 0;
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;

		if (anim)
			anim->animState = mState;

		GetRandomPositionNavMesh(me->GetActorLocation(), 500, randomPos);
	}
}

void UEnemyFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0;

		if (anim)
			anim->animState = mState;
	}
}

void UEnemyFSM::DieState()
{
	if (anim && anim->bDieDone == false)
		return;

	// 등속 운동 공식 : P = P0 + vt
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	
	me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		me->Destroy();
	}
}

