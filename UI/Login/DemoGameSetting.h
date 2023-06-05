// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoGameSetting.generated.h"

class USlider;
class UComboBoxString;
class UCheckBox;
/**
 *
 */
UCLASS()
class DEMO_API UDemoGameSetting: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UCheckBox *FullScreenCheck;

	UPROPERTY(meta = (BindWidget))
	UCheckBox *WindowCheck;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString *ResolutionCombo;

	UPROPERTY(meta = (BindWidget))
	USlider *SoundSlider;

public:
	UDemoGameSetting(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	//是否全屏
	UFUNCTION()
	void IsFullScreen(bool bIsChecked);

	//是否窗口
	UFUNCTION()
	void IsWindow(bool bIsChecked);

	//分辨率选择变化时
	UFUNCTION()
	void SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	//声音值改变
	UFUNCTION()
	void ValueChanged(float Value);
};
