// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameContinue.h"

#include "Components/Button.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void UDemoGameContinue::NativeConstruct()
{
	Super::NativeConstruct();

	LoadSaveButton1->OnClicked.AddDynamic(this, &UDemoGameContinue::LoadSaveGame);
}

void UDemoGameContinue::LoadSaveGame()
{
	if(!GetWorld())
	{
		return;
	}

	FString Map = "ThirdPersonMap";
	UGameplayStatics::OpenLevel(this, FName(* Map), true);

	if(ADemoGameStateBase *StateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
	{
		StateBase->ChangedNewGame(false);
	}
}
