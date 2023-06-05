// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoGameContinue.generated.h"

class UButton;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoGameContinue : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock *TimeText;

	UPROPERTY(meta = (BindWidget))
	UImage *PlayerImage;

	UPROPERTY(meta = (BindWidget))
	UButton *LoadSaveButton1;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void LoadSaveGame();
};
