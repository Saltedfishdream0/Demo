// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoSaveAndLoad.h"

#include "Components/Button.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UDemoSaveAndLoad::NativeConstruct()
{
	Super::NativeConstruct();

	SaveGameButton->OnClicked.AddDynamic(this, &UDemoSaveAndLoad::SaveGame);

	ExitGameButton->OnClicked.AddDynamic(this, &UDemoSaveAndLoad::ExitGame);
}

void UDemoSaveAndLoad::SaveGame()
{
	if(ADemoGameStateBase *StateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
	{
		StateBase->SavePlayerData();
	}
}

void UDemoSaveAndLoad::ExitGame()
{
	if(!ExitGameButton)
	{
		return;
	}

	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
