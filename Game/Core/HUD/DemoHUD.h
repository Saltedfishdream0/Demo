// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DemoHUD.generated.h"

class UGameMainUI;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoHUD: public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UGameMainUI> GameMainUIClass;

	UGameMainUI *GameUI;

public:
	ADemoHUD();

	virtual void BeginPlay() override;

	FORCEINLINE UGameMainUI *GetGameMainUI() { return GameUI; }
};
