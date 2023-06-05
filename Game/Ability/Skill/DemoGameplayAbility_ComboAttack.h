// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Ability/DemoGameplayAbility.h"
#include "DemoGameplayAbility_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoGameplayAbility_ComboAttack: public UDemoGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo *ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData *TriggerEventData) override;
};
