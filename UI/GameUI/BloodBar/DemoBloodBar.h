// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoBloodBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoBloodBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UProgressBar *BloodBar;

public:
	void SetBloodPercent(float Value);
};
