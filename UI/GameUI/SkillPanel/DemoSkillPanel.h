// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoSkillPanel.generated.h"

class UHorizontalBox;
class UDemoSkillSlot;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoSkillPanel: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox *SkillArray;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UDemoSkillSlot> SKillSlotClass;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

	//初始化技能槽
	void InitSkill();

	//更新冷却
	UFUNCTION()
	void UpdateCoolDown(const FName &Name, float Value);
};
