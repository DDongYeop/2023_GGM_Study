// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

//  �� ĳ���� ���� ����
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
	//  ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;


public:
	void OnDamageProcess();

	bool GetRandomPositionNavMesh(FVector centerLocation, float radius, FVector& dest);

public:
	// ��� ����
	void IdleState();
	// �̵� ����
	void MoveState();
	// ���� ����
	void AttackState();
	// �ǰ� ����
	void DamageState();
	// ���� ����
	void DieState();		

// ��� ����
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float idleDelayTime = 2;

	// ��� �ð�
	float currentTime = 0;

// �̵� ����
public:
	UPROPERTY(VisibleAnywhere, Category = FSM)
	TObjectPtr<class ATPSCharacterPlayer> target;

	UPROPERTY()
	TObjectPtr<class AEnemy> me;

// ���� ����
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 2.0f;

// �ǰ� ����
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	int32 hp = 3;

	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2.0f;

// ���� ����
public:
	UPROPERTY(EditAnywhere, Category = FSM)
	float dieSpeed = 50.0f;

public:
	// ������� �ִϸ��̼� �������Ʈ ���� ������
	class UEnemyAnim* anim;

	// enemy�� �����ϰ� �ִ� AIController
	UPROPERTY()
	class AAIController* ai;

	FVector randomPos;
};
