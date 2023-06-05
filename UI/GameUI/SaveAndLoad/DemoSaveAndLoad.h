// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoSaveAndLoad.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoSaveAndLoad: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton *SaveGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton *ExitGameButton;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void ExitGame();
};
