// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"

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

	// 월드에 배치되거나 스폰될 때 자동으로 AIController부터 Proccess 될 수 있도록 설정
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

void AEnemy::OnDamageProcess()
{
	if (fsm)
	{
		fsm->OnDamageProcess();
	}
}

