// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "EnemyAnim.h"
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

	target = Cast<ATPSCharacterPlayer>(actor);
	
	me = Cast<AEnemy>(GetOwner());

	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
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

		// �а� �ִϸ��̼� ���
		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage"), index);
		if (anim)
		{
			anim->PlayDamageAnim(FName(*sectionName));
		}
	}
	else
	{
		mState = EEnemyState::Die;
		// ĸ�� ��Ȱ��ȭ
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (anim)
		anim->animState = mState;
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
	}
}

void UEnemyFSM::MoveState()
{
	if (target == nullptr || me == nullptr)
		return;

	// Ÿ���� ������
	FVector dest = target->GetActorLocation();

	// ����
	FVector dir = dest - me->GetActorLocation();

	// �̵�
	me->AddMovementInput(dir.GetSafeNormal());

	// Ÿ�ٰ� �Ÿ��� ����� ����
	if (dir.Size() < attackRange)
	{
		mState = EEnemyState::Attack;
		currentTime = attackDelayTime;

		if (anim)
		{
			anim->animState = mState;
			anim->bAttackPlay = true;
		}
	}
}

void UEnemyFSM::AttackState()
{
	currentTime += GetWorld()->GetDeltaSeconds();

	if (currentTime > attackDelayTime)
	{
		// �����ϱ�
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
	// ��� � ���� : P = P0 + vt
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	
	me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		me->Destroy();
	}
}

