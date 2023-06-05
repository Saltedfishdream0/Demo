// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoGameMode.h"

#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Game/Core/HUD/DemoHUD.h"

ADemoGameModeBase::ADemoGameModeBase()
{
	DefaultPawnClass = ADemoPlayerCharacter::StaticClass();
	GameStateClass   = ADemoGameStateBase::StaticClass();
	HUDClass         = ADemoHUD::StaticClass();
}
