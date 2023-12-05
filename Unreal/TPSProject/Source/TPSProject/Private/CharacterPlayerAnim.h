// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class UCharacterPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCharacterPlayerAnim();

public:
	// 매 프레임마다 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

public:
	// 공격 애니메이션 재생 함수
	void PlayAttackAnim();

	// 피격 애니메이션 재생 함수
	void PlayHitAnim();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	bool isInAir = false;

public:
	UPROPERTY(VisibleAnywhere, Category = PlayerAnim)
	TObjectPtr<class UAnimMontage> attackAnimMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnim)
	TObjectPtr<class UAnimMontage> hitAnimMontage;
};
