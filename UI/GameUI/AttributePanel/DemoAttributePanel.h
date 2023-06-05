// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoAttributePanel.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoAttributePanel: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock *LeveText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *ExpText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *HealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *ManaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *StaminaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *AttackText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *DefenseText;

public:
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
};
