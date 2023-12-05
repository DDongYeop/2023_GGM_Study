// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "EnemyInterface.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 등록하기
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	if (collisionComp)
	{
		collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
		collisionComp->SetSphereRadius(13);
		collisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

		RootComponent = collisionComp;
	}

	// 메쉬 등록하기
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	if (bodyMeshComp)
	{
		bodyMeshComp->SetupAttachment(RootComponent);
		bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bodyMeshComp->SetRelativeScale3D(FVector(0.25));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		if (BodyMeshRef.Object)
		{
			bodyMeshComp->SetStaticMesh(BodyMeshRef.Object);
			bodyMeshComp->SetRelativeLocation(FVector(0, 0, -12.5));
		}
	}

	//  발사체 움직임 컴포넌트
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	if (movementComp)
	{
		movementComp->SetUpdatedComponent(collisionComp);
		movementComp->InitialSpeed = 5000;
		movementComp->MaxSpeed = 5000;
		movementComp->bShouldBounce = true;
		movementComp->Bounciness = 0.3f;
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	// 생명주기 조절
	//InitialLifeSpan = 2.0f;

	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Die()
{
	Destroy();
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		IEnemyInterface* DamageInterface = Cast<IEnemyInterface>(OtherActor);
		if (DamageInterface)
		{
			AActor* parent = GetOwner();
			DamageInterface->OnDamageProcess(parent);
			Die();
		}
	}
}

