// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Ability/DemoGameplayAbility.h"
#include "DemoGameplayAbility_Potion.generated.h"

class UDemoPotion;
/**
 *
 */
UCLASS()
class DEMO_API UDemoGameplayAbility_Potion: public UDemoGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Potion)
	UDemoPotion *Potion;

	UPROPERTY(EditDefaultsOnly, Category = Potion)
	int32 Num;

public:
	virtual void OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload) override;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo *ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData *TriggerEventData) override;
};
