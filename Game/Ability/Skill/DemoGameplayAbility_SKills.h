// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Ability/DemoGameplayAbility.h"
#include "DemoGameplayAbility_SKills.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoGameplayAbility_SKills: public UDemoGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo *ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData *TriggerEventData) override;

	//更新CD
	void UpdateCD();
};
