// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

ATPSGameModeBase::ATPSGameModeBase()
{
	// DefaultPawnClass
	static ConstructorHelpers::FClassFinder<APawn> CharacterPlayerRef(TEXT("/Script/Engine.Blueprint'/Game/ProjectContent/Blueprints/BP_TPSCharacterPlayer.BP_TPSCharacterPlayer_C'"));
	if (CharacterPlayerRef.Class)
	{
		DefaultPawnClass = CharacterPlayerRef.Class;
	}

	// PlayerControllerClass
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(TEXT("/Script/CoreUObject.Class'/Script/TPSProject.TPSPlayerController'"));
	if (PlayerControllerRef.Class)
	{
		PlayerControllerClass = PlayerControllerRef.Class;
	}	
}
