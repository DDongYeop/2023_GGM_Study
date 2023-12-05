// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "TPSCharacterPlayer.h"
#include <Components/SphereComponent.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Model/vampire_a_lusth.vampire_a_lusth'"));
	if (EnemyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(EnemyMeshRef.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.84f));
	}

	//static ConstructorHelpers::FClassFinder<UAnimInstance> EnemyAnimRef(TEXT("/Game/ProjectContent/Animations/ABP_Enemy.ABP_Enemy_C"));
	//if (EnemyAnimRef.Class)
	//{
	//	GetMesh()->SetAnimInstanceClass(EnemyAnimRef.Class);
	//}

	// EnemyFSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (sphereComponent)
	{
		sphereComponent->SetupAttachment(RootComponent);
		sphereComponent->SetCollisionProfileName(TEXT("TargetOverlap"));
		sphereComponent->SetSphereRadius(detectRadius);

		sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::MyBeginOverlap);
		sphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemy::MyEndOverlap);
	}

	// 월드에 배치되거나 스폰될 때 자동으로 AIController부터 Prossess 될 수 있도록 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnDamageProcess(AActor* AttackActor)
{
	if (fsm)
	{
		fsm->OnDamageProcess();

		ATPSCharacterPlayer* target = Cast<ATPSCharacterPlayer>(AttackActor);
		if (target)
		{
			fsm->target = target;
		}
	}
}

void AEnemy::MyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATPSCharacterPlayer* target = Cast<ATPSCharacterPlayer>(OtherActor);

	if (target)
	{
		if (fsm)
			fsm->target = target;

		DrawDebugSphere(GetWorld(), GetActorLocation(), detectRadius, 16, FColor::Red, false, 2.0f);
	}
}

void AEnemy::MyEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATPSCharacterPlayer* target = Cast<ATPSCharacterPlayer>(OtherActor);

	if (target)
	{
		if (fsm)
			fsm->target = nullptr;
	}
}

