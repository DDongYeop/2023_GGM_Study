// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 랜덤 시간 간격 (최소값)
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	float minTime = 1.0f;

	// 랜덤 시간 간격 (최대값)
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	float maxTime = 3.0f;

	// 스폰할 위치 배열
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> spawnPoints;

	// Enemy 타입의 블루프린트 할당 변수
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TSubclassOf<class AEnemy> enemyFactory;

	// 스폰을 위한 알람 타이머
	FTimerHandle spawnTimerHandle;

public:
	// 적 생성 함수
	void CreateEnemy();

	// 동적으로 스폰할 위치 찾아 할당하는 함수
	void FindSpawnPoints();
};
