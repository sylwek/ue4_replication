// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestProject_F51HUD.generated.h"

UCLASS()
class ATestProject_F51HUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestProject_F51HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

