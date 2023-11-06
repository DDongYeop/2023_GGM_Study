// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 총알 제거 함수
	void Die();

public:
	// 충돌체 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Collision)
	TObjectPtr<class USphereComponent> collisionComp;

	// 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = BodyMesh)
	TObjectPtr<class UStaticMeshComponent> bodyMeshComp;

	// 발사체의 이동 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<class UProjectileMovementComponent> movementComp;
};
