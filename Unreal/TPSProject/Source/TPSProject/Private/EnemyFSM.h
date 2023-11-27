// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

//  적 캐릭터 상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: 
	//  상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;


public:
	void OnDamageProcess();

	bool GetRandomPositionNavMesh(FVector centerLocation, float radius, FVector& dest);

public:
	// 대기 상태
	void IdleState();
	// 이동 상태
	void MoveState();
	// 공격 상태
	void AttackState();
	// 피격 상태
	void DamageState();
	// 죽음 상태
	void DieState();		

// 대기 상태
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float idleDelayTime = 2;

	// 경과 시간
	float currentTime = 0;

// 이동 상태
public:
	UPROPERTY(VisibleAnywhere, Category = FSM)
	TObjectPtr<class ATPSCharacterPlayer> target;

	UPROPERTY()
	TObjectPtr<class AEnemy> me;

// 공격 상태
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 2.0f;

// 피격 상태
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	int32 hp = 3;

	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2.0f;

// 죽음 상태
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float dieSpeed = 50.0f;

public:
	// 사용중인 애니메이션 블루프린트 참조 포인터
	class UEnemyAnim* anim;

	// enemy를 소유하고 있는 AIController
	UPROPERTY()
	class AAIController* ai;

	FVector randomPos;
};
