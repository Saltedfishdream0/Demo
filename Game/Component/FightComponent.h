// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "FightComponent.generated.h"

class ADemoPlayerCharacter;
class UDemoAbilitySystemComponent;
class UGameplayAbility;
class ADemoCharacterBase;

USTRUCT(BlueprintType)
struct DEMO_API FComboAttack
{
	GENERATED_USTRUCT_BODY()

	FComboAttack();

	//判断是否长按
	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bLongPressed;

	//判断是否短按
	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bShorPressed;

	//连击序号
	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	int32 ComboIndex;

	//最大连击数
	UPROPERTY()
	int32 MaxIndex;

	//回调GA触发普通攻击
	ADemoPlayerCharacter *PlayerCharacter;

	UPROPERTY()
	FName ComboKey;

	//鼠标按下时
	void Pressed();

	//松开鼠标时
	void Released();

	//动画结束时
	void EndAnimation();

	//下一个动画
	void AnimationIndex();
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEMO_API UFightComponent: public UActorComponent
{
	GENERATED_BODY()

	/*//攻击蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, meta = (AllowPrivateAccess = "true"))
	UAnimMontage *AttackMontage;*/

	UPROPERTY()
	FComboAttack ComboAttack;

	/*//必须把Handle放在TMap里面,不然找不到
	UPROPERTY()
	TMap<FName, FGameplayAbilitySpecHandle> Skills;*/

public:
	// Sets default values for this component's properties
	UFightComponent();

	//触发攻击
	void ComboAttackPressed();
	//结束攻击
	void ComboAttackReleased();
	//重置攻击
	void ResetComboAttack();

	FORCEINLINE FComboAttack *GetComboAttack() { return & ComboAttack; }

	/*//注册能力
	FGameplayAbilitySpecHandle RegisterGameAbility(TArray<UGameplayAbility*> InAbility);

	//激活技能
	void ActiveSkill(FGameplayTag SkillName);
	void ActiveSkill(const FString &SkillName);

	void Hit();
	void Death();*/

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<UDemoAbilitySystemComponent> AbilitySystemComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<ACharacterBase> CharacterBase;*/
};
