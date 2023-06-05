// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameplayAbility_SKills.h"

#include "Game/Character/Core/DemoCharacterBase.h"

void UDemoGameplayAbility_SKills::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData *TriggerEventData)
{
	if(bHasBlueprintActivate)
	{
		// 蓝图的 Activateability 函数必须在其执行链中的某个位置调用 CommitAbility
		K2_ActivateAbility();
	}
	else if(bHasBlueprintActivateFromEvent)
	{
		if(TriggerEventData)
		{
			// 蓝图的 Activateability 函数必须在其执行链中的某个位置调用 CommitAbility
			K2_ActivateAbilityFromEvent(* TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled        = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
	}
	else
	{
		// 本地子类可能希望重写 ActivateAbility，并执行以下操作：

		// 做的任务...

		if(CommitAbility(Handle, ActorInfo, ActivationInfo)) // ..然后提交能力...
		{
			//	做的事情...

			if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(ActorInfo->OwnerActor))
			{
				UpdateCD();
				//播放第0个蒙太奇片段,配置蒙太奇的时候记得改名字
				if(MontageToPlay(* FString::FromInt(0)))
				{
				}
			}
		}
	}
}

void UDemoGameplayAbility_SKills::UpdateCD()
{
	//拿到配置的CD
	if(UGameplayEffect *CoolDown = GetCooldownGameplayEffect())
	{
		float CDValue;

		//获取持续模式的值
		if(CoolDown->DurationMagnitude.GetStaticMagnitudeIfPossible(GetAbilityLevel(), CDValue) && CDValue != 0.f)
		{
			if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(GetActorInfo().OwnerActor))
			{
				CharacterBase->UpdateCD(* AbilityTags.ToStringSimple(), CDValue);
			}
		}
	}
}
