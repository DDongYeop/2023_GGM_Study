// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "EngineUtils.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	//랜덤 생성 시간 구하기 
	float createTime = FMath::RandRange(minTime, maxTIme);

	//Timer 알림 등록
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

	FindSpawnPoints();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::CreateEnemy()
{
	//랜덤 위치 구하기
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);

	//적 생성
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));

	//다시 랜덤 시간 후에 CreateEnemy 호출
	float createTime = FMath::RandRange(minTime, maxTIme);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	/*for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* spawn = *it;

		if (spawn->GetName().Contains(TEXT("BP_SpawnPoint")))
		{
			spawnPoints.Add(spawn);
		}
	}*/

	TArray<AActor*> allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto spawn : allActors)
	{
		if (spawn->GetName().Contains(TEXT("BP_SpawnPoint")))
		{
			spawnPoints.Add(spawn);
		}
	}
}
