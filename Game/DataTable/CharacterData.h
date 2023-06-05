// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FCharacterData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	//角色ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Table)
	int32 CharacterID;

	//生命
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Health;

	//最大生命
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float MaxHealth;

	//魔法
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Mana;

	//最大魔法
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float MaxMana;

	//耐力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Stamina;

	//最大耐力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float MaxStamina;

	//经验
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Exp;

	//最大经验
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float MaxExp;

	//等级
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Level;

	//金币
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Gold;

	//攻击
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Attack;

	//防御
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float Defense;

	//每级增加的生命
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float AddHealth;

	//每集增加的魔法
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float AddMana;

	//每级增加的经验
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float AddExp;

	//每级增加的攻击
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Table)
	float AddAttack;

	FCharacterData();
};
