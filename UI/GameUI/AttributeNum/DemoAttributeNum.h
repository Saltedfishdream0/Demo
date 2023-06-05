// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoAttributeNum.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoAttributeNum: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Num;

public:
	virtual void NativeConstruct() override;

	void SetTextNum(float NewNum);
	void SetTextColor(const FLinearColor &Color);
};
