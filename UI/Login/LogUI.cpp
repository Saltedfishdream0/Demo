// Fill out your copyright notice in the Description page of Project Settings.


#include "LogUI.h"

#include "DemoGameContinue.h"
#include "DemoGameSetting.h"
#include "Components/Button.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ULogUI::ULogUI(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULogUI::NativeConstruct()
{
	Super::NativeConstruct();

	Start->OnClicked.AddDynamic(this, &ULogUI::BeginGame);
	Continue->OnClicked.AddDynamic(this, &ULogUI::OpenArchive);
	Settings->OnClicked.AddDynamic(this, &ULogUI::OpenSetting);
	Exit->OnClicked.AddDynamic(this, &ULogUI::ExitGame);

	GameSettingPanel->SetVisibility(ESlateVisibility::Hidden);
	GameContinuePanel->SetVisibility(ESlateVisibility::Hidden);
}

void ULogUI::NativeDestruct()
{
	Super::NativeDestruct();

	Start->OnClicked.RemoveDynamic(this, &ULogUI::BeginGame);
	Continue->OnClicked.RemoveDynamic(this, &ULogUI::OpenArchive);
	Settings->OnClicked.RemoveDynamic(this, &ULogUI::OpenSetting);
	Exit->OnClicked.RemoveDynamic(this, &ULogUI::ExitGame);
}

void ULogUI::BeginGame()
{
	if(!Start)
	{
		return;
	}

	FString Map = "ThirdPersonMap";
	UGameplayStatics::OpenLevel(this, FName(* Map), true);

	if(ADemoGameStateBase *StateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
	{
		StateBase->ChangedNewGame(true);
	}
}

void ULogUI::OpenArchive()
{
	GameContinuePanel->SetVisibility(ESlateVisibility::Visible);
	GameSettingPanel->SetVisibility(ESlateVisibility::Hidden);
}

void ULogUI::OpenSetting()
{
	GameContinuePanel->SetVisibility(ESlateVisibility::Hidden);
	GameSettingPanel->SetVisibility(ESlateVisibility::Visible);
}

void ULogUI::ExitGame()
{
	if(!Exit)
	{
		return;
	}

	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
