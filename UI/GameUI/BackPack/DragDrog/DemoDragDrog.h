// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoDragDrog.generated.h"

class UImage;
/**
 *
 */
UCLASS()
class DEMO_API UDemoDragDrog: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UImage *Image;

public:
	void DragImage(UTexture2D *InImage);
};
