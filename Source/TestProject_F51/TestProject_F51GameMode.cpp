// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestProject_F51GameMode.h"
#include "TestProject_F51HUD.h"
#include "TestProject_F51Character.h"
#include "UObject/ConstructorHelpers.h"

ATestProject_F51GameMode::ATestProject_F51GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestProject_F51HUD::StaticClass();
}
