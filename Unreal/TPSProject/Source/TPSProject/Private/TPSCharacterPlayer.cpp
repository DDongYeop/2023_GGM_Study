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

	// ���̷�Ż �޽�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (CharacterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// �ִ� Ŭ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ProjectContent/Animations/ABP_TPSChracterPlayer.ABP_TPSChracterPlayer_C'"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// SpringArm ������Ʈ �߰�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (springArmComp)
	{
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
	}

	// Camera ������Ʈ �߰�
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamComp"));
	if (tpsCamComp)
	{
		tpsCamComp->SetupAttachment(springArmComp);
	}

	// Gun Mesh ������Ʈ �߰�
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

	// ü�� ����
	hp = initalHp;

	// �������۰��� �⺻ ����� ����
	ChangeToSniperGun();

	// �������� UI ���� �ν��Ͻ� ����
	sniperUI = CreateWidget(GetWorld(), sniperUIFactory);

	// ũ�ν���� UI ���� �ν��Ͻ� ����
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
	// Sound ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	// ���� ��Ÿ�� �ִϸ��̼� ���
	auto anim = Cast<UCharacterPlayerAnim>(GetMesh()->GetAnimInstance());
	if (anim)
	{
		anim->PlayAttackAnim();
	}

	// ī�޶� ����ũ ���
	auto controller = GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		controller->PlayerCameraManager->StartCameraShake(cameraShake);
	}

	if (bUsingGrenadeGun)
	{
		// �߻�ü ����
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	else
	{
		// Line Trace ����
		// LineTrace ���� ��ġ
		FVector startPos = tpsCamComp->GetComponentLocation();

		// LineTrace ���� ��ġ
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;

		// LineTrace �浹 ���� ����
		FHitResult hitInfo;

		// �浹 �ɼ� ���� ����
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

		// �浹
		if (bHit)
		{
			// �浹ó��
			FTransform bulletTrans;
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

			// ���� ��� ����
			auto hitComp = hitInfo.GetComponent();
			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;

				hitComp->AddForce(force);
			}

			/*
			// �� �浹 ó��
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
