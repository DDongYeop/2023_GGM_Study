// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacterPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Bullet.h"
#include "Particles/ParticleSystem.h"
#include "CharacterPlayerAnim.h"
#include "EnemyFSM.h"
#include "EnemyInterface.h"

// Sets default values
ATPSCharacterPlayer::ATPSCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (CharacterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// 애님 클래스
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ProjectContent/Animations/ABP_TPSChracterPlayer.ABP_TPSChracterPlayer_C'"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// SpringArm 컴포넌트 추가
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (springArmComp)
	{
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
	}

	// Camera 컴포넌트 추가
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamComp"));
	if (tpsCamComp)
	{
		tpsCamComp->SetupAttachment(springArmComp);
	}

	// Gun Mesh 컴포넌트 추가
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	if (gunMeshComp)
	{
		gunMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

		static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
		if (GunMeshRef.Object)
		{
			gunMeshComp->SetSkeletalMesh(GunMeshRef.Object);
			gunMeshComp->SetRelativeLocation(FVector(-17, 10, -3));
			gunMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
		}
	}

	// sniper Mesh Component
	sniperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunMesh"));
	if (sniperMeshComp)
	{
		sniperMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SniperMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/SniperGun/sniper1.sniper1'"));
		if (SniperMeshRef.Object)
		{
			sniperMeshComp->SetStaticMesh(SniperMeshRef.Object);
			sniperMeshComp->SetRelativeLocation(FVector(-42, 7, 1));
			sniperMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
			sniperMeshComp->SetRelativeScale3D(FVector(0.15f));
		}
	}

	/* Subclass */
	static ConstructorHelpers::FClassFinder<ABullet> BulletRef(TEXT("/Script/Engine.Blueprint'/Game/ProjectContent/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (BulletRef.Class)
	{
		bulletFactory = BulletRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SniperAimUIRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ProjectContent/Blueprints/WBP_SniperUI.WBP_SniperUI_C'"));
	if (SniperAimUIRef.Class)
	{
		sniperUIFactory = SniperAimUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CrosshairUIRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ProjectContent/Blueprints/WBP_Crosshair.WBP_Crosshair_C'"));
	if (CrosshairUIRef.Class)
	{
		crosshairUIFactory = CrosshairUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CameraShakeRef(TEXT("/Script/Engine.Blueprint'/Game/ProjectContent/Blueprints/BP_CameraShake.BP_CameraShake_C'"));
	if (CameraShakeRef.Class)
	{
		cameraShake = CameraShakeRef.Class;
	}

	// Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BulletEffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProjectContent/Paticles/P_BulletEffect.P_BulletEffect'"));
	if (BulletEffectRef.Object)
	{
		bulletEffectFactory = BulletEffectRef.Object;
	}

	// Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> BulletSoundRef(TEXT("/Script/Engine.SoundWave'/Game/SniperGun/Rifle.Rifle'"));
	if (BulletSoundRef.Object)
	{
		bulletSound = BulletSoundRef.Object;
	}

	/* Input */
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ProjectContent/Input/IMC_TPS.IMC_TPS'"));
	if (IMCRef.Object)
	{
		IMC_TPS = IMCRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveForwardRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/MoveForward.MoveForward'"));
	if (MoveForwardRef.Object)
	{
		MoveForwardAction = MoveForwardRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveRightRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/MoveRight.MoveRight'"));
	if (MoveRightRef.Object)
	{
		MoveRightAction = MoveRightRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnPitchRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/TurnPitch.TurnPitch'"));
	if (TurnPitchRef.Object)
	{
		TurnPitchAction = TurnPitchRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnYawRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/TurnYaw.TurnYaw'"));
	if (TurnYawRef.Object)
	{
		TurnYawAction = TurnYawRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/Jump.Jump'"));
	if (JumpRef.Object)
	{
		JumpAction = JumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> FireRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/Fire.Fire'"));
	if (FireRef.Object)
	{
		FireAction = FireRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> GrenadeGunActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/GrenadeGun.GrenadeGun'"));
	if (GrenadeGunActionRef.Object)
	{
		GrenadeGunAction = GrenadeGunActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SniperGunActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/SniperGun.SniperGun'"));
	if (SniperGunActionRef.Object)
	{
		SniperGunAction = SniperGunActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SniperAimActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/Aim.Aim'"));
	if (SniperAimActionRef.Object)
	{
		SniperAimAction = SniperAimActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> RunActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectContent/Input/Run.Run'"));
	if (RunActionRef.Object)
	{
		RunAction = RunActionRef.Object;
	}
}

// Called when the game starts or when spawned
void ATPSCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	// 체력 설정
	hp = initalHp;

	// 스나이퍼건을 기본 무기로 셋팅
	ChangeToSniperGun();

	// 스나이퍼 UI 위젯 인스턴스 생성
	sniperUI = CreateWidget(GetWorld(), sniperUIFactory);

	// 크로스헤어 UI 위젯 인스턴스 생성
	crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);

	if (crosshairUI)
		crosshairUI->AddToViewport();
}

// Called every frame
void ATPSCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMC_TPS, 0);
		}
	}

	// bindings
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		// MoveForward
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::MoveForward);

		// MoveRight
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::MoveRight);

		// TurnPitch
		EnhancedInputComponent->BindAction(TurnPitchAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::TurnPitch);

		// TurnYaw
		EnhancedInputComponent->BindAction(TurnYawAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::TurnYaw);

		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::InputFire);

		// GrenadeGun
		EnhancedInputComponent->BindAction(GrenadeGunAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::ChangeToGrenadeGun);

		// SniperGun
		EnhancedInputComponent->BindAction(SniperGunAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::ChangeToSniperGun);

		// SniperAim
		EnhancedInputComponent->BindAction(SniperAimAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::SniperAim);

		// Run
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::InputRun);
	}
}

void ATPSCharacterPlayer::MoveForward(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, Movement);
	}
}

void ATPSCharacterPlayer::MoveRight(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, Movement);
	}
}

void ATPSCharacterPlayer::TurnPitch(const FInputActionValue& Value)
{
	float Turn = -(Value.Get<float>());
	if (Controller != nullptr)
	{
		AddControllerPitchInput(Turn);
	}
}

void ATPSCharacterPlayer::TurnYaw(const FInputActionValue& Value)
{
	float Turn = Value.Get<float>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(Turn);
	}
}

void ATPSCharacterPlayer::InputFire(const FInputActionValue& Value)
{
	// Sound 재생
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	// 공격 몽타주 애니메이션 재생
	auto anim = Cast<UCharacterPlayerAnim>(GetMesh()->GetAnimInstance());
	if (anim)
	{
		anim->PlayAttackAnim();
	}

	// 카메라 셰이크 재생
	auto controller = GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		controller->PlayerCameraManager->StartCameraShake(cameraShake);
	}

	if (bUsingGrenadeGun)
	{
		// 발사체 생성
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	else
	{
		// Line Trace 설정
		// LineTrace 시작 위치
		FVector startPos = tpsCamComp->GetComponentLocation();

		// LineTrace 종료 위치
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;

		// LineTrace 충돌 정보 변수
		FHitResult hitInfo;

		// 충돌 옵션 설정 변수
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

		// 충돌
		if (bHit)
		{
			// 충돌처리
			FTransform bulletTrans;
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

			// 물리 기능 적용
			auto hitComp = hitInfo.GetComponent();
			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;

				hitComp->AddForce(force);
			}

			/*
			// 적 충돌 처리
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy)
			{
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				if (enemyFSM)
					enemyFSM->OnDamageProcess();
			}
			*/

			IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(hitInfo.GetActor());
			if (EnemyInterface)
			{
				EnemyInterface->OnDamageProcess();
			}
		}
	}
}

void ATPSCharacterPlayer::InputRun(const FInputActionValue& Value)
{
	bool IsRun = Value.Get<bool>();
	if (IsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	}
}

void ATPSCharacterPlayer::ChangeToGrenadeGun()
{
	bUsingGrenadeGun = true;
	if (gunMeshComp)
		gunMeshComp->SetVisibility(true);
	if (sniperMeshComp)
		sniperMeshComp->SetVisibility(false);
}

void ATPSCharacterPlayer::ChangeToSniperGun()
{
	bUsingGrenadeGun = false;
	if (gunMeshComp)
		gunMeshComp->SetVisibility(false);
	if (sniperMeshComp)
		sniperMeshComp->SetVisibility(true);
}

void ATPSCharacterPlayer::SniperAim(const FInputActionValue& Value)
{
	if (bUsingGrenadeGun)
		return;

	bool SniperAim = Value.Get<bool>();
	if (SniperAim)
	{
		if (sniperUI)
			sniperUI->AddToViewport();
		if (crosshairUI)
			crosshairUI->RemoveFromParent();
		if (tpsCamComp)
			tpsCamComp->SetFieldOfView(45.0f);
	}
	else
	{
		if (sniperUI)
			sniperUI->RemoveFromParent();
		if (crosshairUI)
			crosshairUI->AddToViewport();
		if (tpsCamComp)
			tpsCamComp->SetFieldOfView(90.0f);
	}
}

void ATPSCharacterPlayer::OnHitEvent()
{
	UE_LOG(LogTemp, Log, TEXT("Damaged!"));

	hp--;
	if (hp <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Player is dead!"));
	}
}
