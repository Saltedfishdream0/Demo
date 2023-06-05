// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Component/BackPackComponent.h"
#include "GameFramework/SaveGame.h"
#include "DemoSaveGame.generated.h"

class UDemoItem;

USTRUCT()
struct FDemoPlayerData
{
	GENERATED_USTRUCT_BODY()

	FDemoPlayerData();

	//玩家的位置
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	FVector PlayerVector;

	//玩家的等级
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerLevel;

	//玩家的生命
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerHealth;

	//玩家的魔法
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerMana;

	//玩家的经验
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerExp;

	//玩家的经验
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerMaxExp;

	//玩家的攻击
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	float PlayerAttack;

	//背包里面的东西
	UPROPERTY(VisibleAnywhere, Category = SaveData)
	TArray<FDemoBackPackItem> BackPackItemArray;
};

/**
 *
 */

UCLASS()
class DEMO_API UDemoSaveGame: public USaveGame
{
	GENERATED_BODY()

	UPROPERTY()
	FDemoPlayerData PlayerDataArray;

public:
	UDemoSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	FORCEINLINE FDemoPlayerData &GetPlayerDataArray() { return PlayerDataArray; }
};
