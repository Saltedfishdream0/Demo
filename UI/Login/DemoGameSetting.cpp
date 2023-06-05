// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameSetting.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"

UDemoGameSetting::UDemoGameSetting(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDemoGameSetting::NativeConstruct()
{
	Super::NativeConstruct();

	FullScreenCheck->OnCheckStateChanged.AddDynamic(this, &UDemoGameSetting::IsFullScreen);
	WindowCheck->OnCheckStateChanged.AddDynamic(this, &UDemoGameSetting::IsWindow);
	ResolutionCombo->OnSelectionChanged.AddDynamic(this, &UDemoGameSetting::SelectionChanged);
	SoundSlider->OnValueChanged.AddDynamic(this, &UDemoGameSetting::ValueChanged);
}

void UDemoGameSetting::NativeDestruct()
{
	Super::NativeDestruct();

	FullScreenCheck->OnCheckStateChanged.RemoveDynamic(this, &UDemoGameSetting::IsFullScreen);
	WindowCheck->OnCheckStateChanged.RemoveDynamic(this, &UDemoGameSetting::IsWindow);
	ResolutionCombo->OnSelectionChanged.RemoveDynamic(this, &UDemoGameSetting::SelectionChanged);
	SoundSlider->OnValueChanged.RemoveDynamic(this, &UDemoGameSetting::ValueChanged);
}

void UDemoGameSetting::IsFullScreen(bool bIsChecked)
{
	FullScreenCheck->SetCheckedState(ECheckBoxState::Checked);
	WindowCheck->SetCheckedState(ECheckBoxState::Unchecked);

	UGameUserSettings *GameUserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();
	if(GameUserSettings)
	{
		GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		GameUserSettings->ApplySettings(true);
	}
}

void UDemoGameSetting::IsWindow(bool bIsChecked)
{
	FullScreenCheck->SetCheckedState(ECheckBoxState::Unchecked);
	WindowCheck->SetCheckedState(ECheckBoxState::Checked);

	UGameUserSettings *GameUserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();
	if(GameUserSettings)
	{
		GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
		GameUserSettings->ApplySettings(true);
	}
}

void UDemoGameSetting::SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FIntPoint Point;
	FString SelectionTmp = ResolutionCombo->GetSelectedOption();
	FString R, L;
	SelectionTmp.Split(TEXT("*"), & R, & L);
	Point.X = FCString::Atoi(* R);
	Point.Y = FCString::Atoi(* L);

	UGameUserSettings *GameUserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();
	if(GameUserSettings)
	{
		GameUserSettings->SetScreenResolution(Point);
		GameUserSettings->ApplySettings(true);
	}
}

void UDemoGameSetting::ValueChanged(float Value)
{
}
