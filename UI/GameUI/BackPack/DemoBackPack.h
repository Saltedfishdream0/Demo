// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/Component/BackPackComponent.h"
#include "Slot/BackPackSlot.h"
#include "DemoBackPack.generated.h"

class UBackPackSlot;
class UUniformGridPanel;
/**
 *
 */
UCLASS()
class DEMO_API UDemoBackPack: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel *BackPackSlotPanel;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UBackPackSlot> BackPackSlotClass;

public:
	UDemoBackPack(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	//初始化背包
	void InitBackpack();

	//处理背包变化的信息
	UFUNCTION()
	void OnBackPackSlot(TArray<FDemoBackPackItem> DemoBackPackClass);
};
