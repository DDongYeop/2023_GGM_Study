// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	// 상태 정보 기억 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	EEnemyState animState;

	// 공격 상태 재생여부 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	bool bAttackPlay = false;

	UFUNCTION(BlueprintCallable, Category=FSMEvent)
	void OnEndAttackAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category=FSMEvent)
	void PlayDamageAnim(FName sectionName);
};
