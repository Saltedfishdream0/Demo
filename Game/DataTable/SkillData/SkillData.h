// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

class UGameplayAbility;
/**
 *
 */
USTRUCT(BlueprintType)
struct FSkillData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	int32 CharacterID;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	UTexture2D *Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	FSkillData();
};
