// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DemoAbilityTask_PMAW.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMontageWaitSimpleForDamageEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */
UCLASS()
class DEMO_API UDemoAbilityTask_PMAW: public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:
	UDemoAbilityTask_PMAW();

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleForDamageEventDelegate DamageEventDelegate;

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	static UDemoAbilityTask_PMAW *CreatePlayMontageAndWaitProxy(
		UGameplayAbility *OwningAbility,
		FName TaskInstanceName,
		UAnimMontage *MontageToPlay,
		FGameplayTagContainer InEventTags,
		float Rate                           = 1.f,
		FName StartSection                   = NAME_None,
		bool bStopWhenAbilityEnds            = true,
		float AnimRootMotionTranslationScale = 1.f,
		float StartTimeSeconds               = 0.f);

private:
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData *Payload);

	FDelegateHandle DelegateHandle;

	UPROPERTY()
	FGameplayTagContainer EventTags;
};
