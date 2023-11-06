// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerAnim.h"
#include "TPSCharacterPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

UCharacterPlayerAnim::UCharacterPlayerAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProjectContent/Animations/Fire_Rifle_Ironsights_Montage.Fire_Rifle_Ironsights_Montage'"));
	if (AttackAnimMontageRef.Object)
	{
		attackAnimMontage = AttackAnimMontageRef.Object;
	}
}

void UCharacterPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 소유 폰 얻어오기
	APawn* ownerPawn = TryGetPawnOwner();

	ATPSCharacterPlayer* player = Cast<ATPSCharacterPlayer>(ownerPawn);
	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forward = player->GetActorForwardVector();
		speed = FVector::DotProduct(forward, velocity);

		FVector right = player->GetActorRightVector();
		direction = FVector::DotProduct(right, velocity);

		UCharacterMovementComponent* movement = player->GetCharacterMovement();
		if (movement)
		{
			isInAir = movement->IsFalling();
		}
	}
}

void UCharacterPlayerAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}
