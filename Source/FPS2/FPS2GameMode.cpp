// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS2GameMode.h"
#include "FPS2HUD.h"
#include "FPS2Character.h"
#include "UObject/ConstructorHelpers.h"

AFPS2GameMode::AFPS2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS2HUD::StaticClass();
}
