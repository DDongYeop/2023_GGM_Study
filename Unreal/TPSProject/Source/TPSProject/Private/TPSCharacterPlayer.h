// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TPSCharacterPlayer.generated.h"

UCLASS()
class ATPSCharacterPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacterPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Input Function
protected:
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void TurnPitch(const FInputActionValue& Value);
	void TurnYaw(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);
	void InputRun(const FInputActionValue& Value);
	void ChangeToGrenadeGun();
	void ChangeToSniperGun();
	void SniperAim(const FInputActionValue& Value);

// 컴포넌트
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> tpsCamComp;

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	TObjectPtr<class USkeletalMeshComponent> gunMeshComp;

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	TObjectPtr<class UStaticMeshComponent> sniperMeshComp;

	// User Widget
	TObjectPtr<class UUserWidget> sniperUI;

	TObjectPtr<class UUserWidget> crosshairUI;

// 클래스
public:
	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditAnywhere, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	UPROPERTY(EditAnywhere, Category = CrosshairUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;

	UPROPERTY(EditAnywhere, Category = CameraMotion)
	TSubclassOf<class UCameraShakeBase> cameraShake;

// 이펙트
public:
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	TObjectPtr<class UParticleSystem> bulletEffectFactory;

// 사운드
public:
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<class USoundBase> bulletSound;

// 캐릭터 이동 속도
public:
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

// 변수
public:
	// 유탄총 사용중인지 여부
	bool bUsingGrenadeGun = true;

	// 스나이퍼가 조준중인지 여부
	bool bSniperAim = false;

// 체력
public:
	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 hp;

	// 초기 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 initalHp = 10;

public:
	UFUNCTION(BlueprintCallable, Category = Health)
	void OnHitEvent();

#pragma region /* Input */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> IMC_TPS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> TurnPitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> TurnYawAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> GrenadeGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SniperGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SniperAimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RunAction;
#pragma endregion
};
