// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilityTask/DemoAbilityTask_PMAW.h"
#include "Game/Character/Core/DemoCharacterBase.h"

UDemoGameplayAbility::UDemoGameplayAbility()
{
}

void UDemoGameplayAbility::OnCompleted()
{
	K2_OnCompleted();
	//结束GA
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDemoGameplayAbility::OnBlendOut()
{
	K2_OnBlendOut();
	//结束GA
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDemoGameplayAbility::OnInterrupted()
{
	K2_OnInterrupted();
	//结束GA
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDemoGameplayAbility::OnCancelled()
{
	K2_OnCancelled();
	//结束GA
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDemoGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload)
{
	//造成伤害后调用Attribute

	//创建一个目标数组
	FGameplayAbilityTargetData_ActorArray *NewTargetData_Actors = new FGameplayAbilityTargetData_ActorArray();
	//把目标传入数组
	NewTargetData_Actors->TargetActorArray.Add(const_cast<AActor*>(Payload.Target));
	//创建目标数据的Handle
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	//把数据添加到处理目标数据的Handle里面
	TargetDataHandle.Add(NewTargetData_Actors);

	for(auto &Tmp : EffectMap)
	{
		FGameplayEffectSpecHandle NewHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Tmp.Value, 1, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));

		if(NewHandle.IsValid())
		{
			FGameplayAbilitySpec *AbilitySpec = GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);

			ApplyAbilityTagsToGameplayEffectSpec(* NewHandle.Data.Get(), AbilitySpec);

			if(AbilitySpec)
			{
				NewHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;
			}
		}

		//数据传入到AttributeSet
		TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(NewHandle, TargetDataHandle);
	}
}

/*void UDemoGameplayAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo *ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData *TriggerEventData)
{
	//最好重写父类的激活能力
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

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

			if(ACharacterBase *CharacterBase = Cast<ACharacterBase>(ActorInfo->OwnerActor))
			{
				//播放第0个蒙太奇片段,配置蒙太奇的时候记得改名字
				if(MontageToPlay(* FString::FromInt(0)))
				{
				}
			}
		}
	}
}*/

void UDemoGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo *ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

UAbilityTask_PlayMontageAndWait *UDemoGameplayAbility::CreatePlayMontageAndWaitProxy(
	FName TaskInstanceName,
	UAnimMontage *MontageToPlay,
	float Rate,
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale,
	float StartTimeSeconds)
{
	UDemoAbilityTask_PMAW *InWait = UDemoAbilityTask_PMAW::CreatePlayMontageAndWaitProxy(
		this,
		TaskInstanceName,
		MontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale,
		StartTimeSeconds);

	if(InWait)
	{
		//把任务绑定到UAbilityTask_PlayMontageAndWait的方法
		InWait->OnCompleted.AddDynamic(this, &UDemoGameplayAbility::OnCompleted);
		InWait->OnBlendOut.AddDynamic(this, &UDemoGameplayAbility::OnBlendOut);
		InWait->OnCancelled.AddDynamic(this, &UDemoGameplayAbility::OnCancelled);
		InWait->OnInterrupted.AddDynamic(this, &UDemoGameplayAbility::OnInterrupted);

		//Task执行完毕以后,绑定命中事件
		InWait->DamageEventDelegate.AddDynamic(this, &UDemoGameplayAbility::OnDamageGameplayEvent);

		//Task创建完成,参数也设置了,调用激活
		InWait->Activate();

		return InWait;
	}

	return nullptr;
}

UAbilityTask_PlayMontageAndWait *UDemoGameplayAbility::MontageToPlay(FName StartSection)
{
	return CreatePlayMontageAndWaitProxy(NAME_None, Montage, 1.f, StartSection);
}
