// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "TPSCharacterPlayer.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	if (Trigger)
	{
		RootComponent = Trigger;
		Trigger->SetCollisionProfileName(TEXT("TargetOverlap"));
		Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::MyBeginOverlap);
	}

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	if (BoxMesh)
	{
		BoxMesh->SetupAttachment(RootComponent);

		static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
		if (BoxMeshRef.Object)
		{
			BoxMesh->SetStaticMesh(BoxMeshRef.Object);
			BoxMesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
			BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));
		}
	}

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	if (Effect)
	{
		Effect->SetupAttachment(RootComponent);
		
		static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/Item/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
		if (EffectRef.Object)
		{
			Effect->SetTemplate(EffectRef.Object);
			Effect->bAutoActivate = false;
		}
	}
}

void AItemBox::MyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATPSCharacterPlayer* player = Cast<ATPSCharacterPlayer>(OtherActor);
	if (player)
	{
		if (Effect)
		{
			Effect->Activate(true);
			Effect->OnSystemFinished.AddDynamic(this, &AItemBox::OnEffectFinished);
		}
		if (BoxMesh)
		{
			BoxMesh->SetHiddenInGame(true);
		}
		SetActorEnableCollision(false);
	}
}

void AItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}


