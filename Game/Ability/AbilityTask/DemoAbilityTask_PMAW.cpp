// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAbilityTask_PMAW.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UDemoAbilityTask_PMAW::UDemoAbilityTask_PMAW()
{
}

void UDemoAbilityTask_PMAW::Activate()
{
	if(Ability != nullptr)
	{
		if(AbilitySystemComponent)
		{
			//拿到施法者的信息
			const FGameplayAbilityActorInfo *ActorInfo = Ability->GetCurrentActorInfo();

			UAnimInstance *AnimInstance = ActorInfo->GetAnimInstance();
			if(AnimInstance)
			{
				//把自己绑定进去  Task创建代理,在系统中绑定代理
				DelegateHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, & UDemoAbilityTask_PMAW::OnDamageGameplayEvent));
			}
		}
	}

	Super::Activate();
}

void UDemoAbilityTask_PMAW::OnDestroy(bool bInOwnerFinished)
{
	if(AbilitySystemComponent)
	{
		//把自己的Tag移除
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, DelegateHandle);
	}

	Super::OnDestroy(bInOwnerFinished);
}

UDemoAbilityTask_PMAW *UDemoAbilityTask_PMAW::CreatePlayMontageAndWaitProxy(
	UGameplayAbility *OwningAbility,
	FName TaskInstanceName,
	UAnimMontage *MontageToPlay,
	FGameplayTagContainer InEventTags,
	float Rate,
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale,
	float StartTimeSeconds)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UDemoAbilityTask_PMAW *MyObj          = NewAbilityTask<UDemoAbilityTask_PMAW>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay                  = MontageToPlay;
	MyObj->Rate                           = Rate;
	MyObj->StartSection                   = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds           = bStopWhenAbilityEnds;
	MyObj->StartTimeSeconds               = StartTimeSeconds;
	MyObj->EventTags                      = InEventTags;

	return MyObj;
}

void UDemoAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData *Payload)
{
	//Task执行完成
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData EventData = * Payload;
		EventData.EventTag           = InGameplayTag;

		//回调GA
		DamageEventDelegate.Broadcast(InGameplayTag, EventData);
	}
}
