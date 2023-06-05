// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoGameStateBase.h"

#include "Abilities/GameplayAbility.h"
#include "Game/Ability/AttributeSet/DemoAttributeSet.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/DemoSaveGame.h"
#include "UI/GameUI/BackPack/DemoBackPack.h"

bool ADemoGameStateBase::bIsNewGame = true;

ADemoGameStateBase::ADemoGameStateBase()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTable(TEXT("/Game/DataTable/SkillTable.SkillTable"));
	SkillDataPtr = SkillDataTable.Object;
}

TArray<UGameplayAbility*> ADemoGameStateBase::GetSkills(int32 InCharacterID)
{
	TArray<UGameplayAbility*> Skills;

	if(GetSkillDataTable())
	{
		if(GetSkillDataTable()->Num() > 0)
		{
			for(auto &Tmp : SkillDatas)
			{
				if(Tmp->CharacterID == InCharacterID)
				{
					UGameplayAbility *NewAbility = Cast<UGameplayAbility>(Tmp->GameplayAbility.GetDefaultObject());

					Skills.Add(NewAbility);
				}
			}
		}
	}

	return Skills;
}

TArray<FSkillData*> *ADemoGameStateBase::GetSkillDataTable()
{
	if(SkillDataPtr)
	{
		SkillDatas.Empty();
		SkillDataPtr->GetAllRows(TEXT("SkillTable"), SkillDatas);
	}

	return & SkillDatas;
}

TArray<FSkillData*> ADemoGameStateBase::GetSkillDataTable(int32 InCharacterID)
{
	TArray<FSkillData*> SkillTables;

	if(GetSkillDataTable()->Num() > 0)
	{
		for(auto &Tmp : SkillDatas)
		{
			if(Tmp->CharacterID == InCharacterID)
			{
				SkillTables.Add(Tmp);
			}
		}
	}

	return SkillTables;
}

void ADemoGameStateBase::SavePlayerData()
{
	if(ADemoPlayerCharacter *PlayerCharacter = GetGameInstance()->GetFirstLocalPlayerController()->GetPawn<ADemoPlayerCharacter>())
	{
		if(UDemoSaveGame *SaveGameInstance = Cast<UDemoSaveGame>(UGameplayStatics::CreateSaveGameObject(UDemoSaveGame::StaticClass())))
		{
			//保存玩家的数据
			SaveGameInstance->GetPlayerDataArray().PlayerVector      = PlayerCharacter->GetActorLocation();
			SaveGameInstance->GetPlayerDataArray().PlayerLevel       = PlayerCharacter->GetAttributeSet()->GetLevel();
			SaveGameInstance->GetPlayerDataArray().PlayerHealth      = PlayerCharacter->GetAttributeSet()->GetMaxHealth();
			SaveGameInstance->GetPlayerDataArray().PlayerMana        = PlayerCharacter->GetAttributeSet()->GetMaxMana();
			SaveGameInstance->GetPlayerDataArray().PlayerExp         = PlayerCharacter->GetAttributeSet()->GetExp();
			SaveGameInstance->GetPlayerDataArray().PlayerMaxExp      = PlayerCharacter->GetAttributeSet()->GetMaxExp();
			SaveGameInstance->GetPlayerDataArray().PlayerAttack      = PlayerCharacter->GetAttributeSet()->GetAttack();
			SaveGameInstance->GetPlayerDataArray().BackPackItemArray = PlayerCharacter->GetBackPackComponent()->GetBackPackArray();

			FString SaveName = "Archived_";

			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveName, 0);

			UE_LOG(LogTemp, Warning, TEXT("Archived Success"));

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Archived Failed"));
}

void ADemoGameStateBase::LoadPlayData()
{
	if(UDemoSaveGame *LoadGame = Cast<UDemoSaveGame>(UGameplayStatics::LoadGameFromSlot("Archived_", 0)))
	{
		if(ADemoPlayerCharacter *PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoPlayerCharacter>())
		{
			//读取玩家数据
			PlayerCharacter->SetActorLocation(LoadGame->GetPlayerDataArray().PlayerVector);
			PlayerCharacter->GetAttributeSet()->SetLevel(LoadGame->GetPlayerDataArray().PlayerLevel);
			PlayerCharacter->GetAttributeSet()->SetMaxHealth(LoadGame->GetPlayerDataArray().PlayerHealth);
			PlayerCharacter->GetAttributeSet()->SetHealth(LoadGame->GetPlayerDataArray().PlayerHealth);
			PlayerCharacter->GetAttributeSet()->SetMaxMana(LoadGame->GetPlayerDataArray().PlayerMana);
			PlayerCharacter->GetAttributeSet()->SetMana(LoadGame->GetPlayerDataArray().PlayerMana);
			PlayerCharacter->GetAttributeSet()->SetExp(LoadGame->GetPlayerDataArray().PlayerExp);
			PlayerCharacter->GetAttributeSet()->SetMaxExp(LoadGame->GetPlayerDataArray().PlayerMaxExp);
			PlayerCharacter->GetAttributeSet()->SetAttack(LoadGame->GetPlayerDataArray().PlayerAttack);
			PlayerCharacter->GetBackPackComponent()->AddBackPackArray(LoadGame->GetPlayerDataArray().BackPackItemArray);

			UE_LOG(LogTemp, Warning, TEXT("Load Success"));

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Load Failed"));
}

bool ADemoGameStateBase::ChangedNewGame(bool Value)
{
	bIsNewGame = Value;

	return bIsNewGame;
}
