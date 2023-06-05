// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "GameMainUI.generated.h"

class UDemoSaveAndLoad;
class UDemoAttributePanel;
class UDemoBackPack;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DEMO_API UGameMainUI: public UUserWidget
{
	GENERATED_BODY()

	//等级文本
	UPROPERTY(meta = (BindWidget))
	UTextBlock *LevelText;

	//生命条
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthBar;

	//魔法条
	UPROPERTY(meta = (BindWidget))
	UProgressBar *ManaBar;

	//耐力条
	UPROPERTY(meta = (BindWidget))
	UProgressBar *StaminaBar;

	//经验条
	UPROPERTY(meta = (BindWidget))
	UProgressBar *ExpBar;

	//背包
	UPROPERTY(meta = (BindWidget))
	UDemoBackPack *BackPackClass;

	//玩家属性面板
	UPROPERTY(meta = (BindWidget))
	UDemoAttributePanel *AttributePanel;

	//保存和读取面板
	UPROPERTY(meta = (BindWidget))
	UDemoSaveAndLoad *SaveAndLoadPanel;

	float TargetHealth;
	float TargetMana;
	float TargetStamina;
	float TargetExp;

public:
	FORCEINLINE UDemoBackPack *GetBackPackClass() { return BackPackClass; }

	UGameMainUI(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void UpdateHealthProgressBar(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateManaProgressBar(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateStaminaProgressBar(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateExpProgressBar(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateLevelProgressBar(float Value);

	//防止物品拖入主UI中,导致隐藏不显示
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;

	//显示和隐藏背包
	void ShowAndHideBackPack();

	//显示和隐藏背包
	void ShowAndHideAttributePanel();

	//显示和隐藏保存游戏
	void ShowAndHideSaveAndLoadPanel();
};
