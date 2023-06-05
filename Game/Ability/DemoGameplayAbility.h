// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DemoGameplayAbility.generated.h"

class ADemoCharacterBase;
class UAbilityTask_PlayMontageAndWait;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoGameplayAbility: public UGameplayAbility
{
	GENERATED_BODY()

public:
	//需要播放的蒙太奇
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage *Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect)
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> EffectMap;

	UDemoGameplayAbility();

	//四个方法绑定到蒙太奇
	UFUNCTION()
	virtual void OnCompleted();
	UFUNCTION()
	virtual void OnBlendOut();
	UFUNCTION()
	virtual void OnInterrupted();
	UFUNCTION()
	virtual void OnCancelled();

	//技能产生伤害后调用
	UFUNCTION()
	virtual void OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload);

	/*//重写父类的激活能力
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo *ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData *TriggerEventData) override;*/

	//重写父类的结束能力
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo *ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

	//给蓝图调用的函数
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnCompleted"))
	void K2_OnCompleted();
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnBlendOut"))
	void K2_OnBlendOut();
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnInterrupted"))
	void K2_OnInterrupted();
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnCancelled"))
	void K2_OnCancelled();

	//绑定信息
	UFUNCTION(BlueprintCallable, Category= "Ability|Tasks", meta = (DisplayName="PlayMontageAndWait"))
	UAbilityTask_PlayMontageAndWait *CreatePlayMontageAndWaitProxy(
		FName TaskInstanceName,
		UAnimMontage *MontageToPlay,
		float Rate                           = 1.f,
		FName StartSection                   = NAME_None,
		bool bStopWhenAbilityEnds            = true,
		float AnimRootMotionTranslationScale = 1.f,
		float StartTimeSeconds               = 0.f);

	//播放蒙太奇动画
	UFUNCTION(BlueprintCallable, Category = "Task|Montage")
	UAbilityTask_PlayMontageAndWait *MontageToPlay(FName StartSection = NAME_None);
};
