// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/DataTable/SkillData/SkillData.h"
#include "GameFramework/GameStateBase.h"
#include "DemoGameStateBase.generated.h"

class UDemoBackPack;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoGameStateBase: public AGameStateBase
{
	GENERATED_BODY()

public:
	ADemoGameStateBase();

	TArray<UGameplayAbility*> GetSkills(int32 InCharacterID);

	TArray<FSkillData*> *GetSkillDataTable();
	TArray<FSkillData*> GetSkillDataTable(int32 InCharacterID);

	//保存数据
	void SavePlayerData();

	//加载游戏
	void LoadPlayData();

	static bool bIsNewGame;

	bool ChangedNewGame(bool Value);

protected:
	TArray<FSkillData*> SkillDatas;

	UPROPERTY()
	UDataTable *SkillDataPtr;
};
