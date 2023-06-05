// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponent.h"

#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Character/Core/DemoCharacterBase.h"

FComboAttack::FComboAttack() :
	bLongPressed(false),
	bShorPressed(false),
	ComboIndex(INDEX_NONE),
	MaxIndex(0),
	PlayerCharacter(nullptr)
{
}

void FComboAttack::Pressed()
{
	//判断是否为第一次攻击
	if (ComboIndex == INDEX_NONE)
	{
		ComboIndex++;

		if (PlayerCharacter)
		{
			PlayerCharacter->ActiveSkillByString("Player.ComboAttack");
		}
	}

	bLongPressed = true;
	bShorPressed = true;
}

void FComboAttack::Released()
{
	bLongPressed = false;
}

void FComboAttack::EndAnimation()
{
	ComboIndex = INDEX_NONE;
}

void FComboAttack::AnimationIndex()
{
	ComboIndex++;

	//判断当前连击是不是大于最大连击,大于就播放第一段
	if (ComboIndex > MaxIndex - 1)
	{
		ComboIndex = 0;
	}
}

// Sets default values for this component's properties
UFightComponent::UFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UFightComponent::ComboAttackPressed()
{
	//TODO 写在BeginPlay里面会出现赋值成功而调用的时候却是空的情况,写在这里就不会  感觉不太合理,目前没找到方法,后面再说
	if (ADemoPlayerCharacter* CharacterBase = GetOwner<ADemoPlayerCharacter>())
	{
		ComboAttack.PlayerCharacter = CharacterBase;
	}

	ComboAttack.Pressed();
}

void UFightComponent::ComboAttackReleased()
{
	ComboAttack.Released();
}

void UFightComponent::ResetComboAttack()
{
	ComboAttack.EndAnimation();
}

// Called when the game starts
void UFightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

/*FGameplayAbilitySpecHandle UFightComponent::RegisterGameAbility(TArray<UGameplayAbility*> InAbility)
{
	if(GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		if(AbilitySystemComponent.IsValid() && InAbility.Num() > 0)
		{
			for(auto &Tmp : InAbility)
			{
				//调用系统注册能力,返回一个Handle
				FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Tmp));

				//拿到技能的Tag
				const FString String = Tmp->AbilityTags.ToStringSimple();

				//转换到FName存入TMap
				Skills.Add(FName(String), Handle);

				//注册连击
				if(String.Equals("Player.ComboAttack"))
				{
					ComboAttack.Player   = Cast<ADemoPlayer>(CharacterBase.Get());
					ComboAttack.ComboKey = "Player.ComboAttack";
					ComboAttack.MaxIndex = Cast<UDemoGameplayAbility>(Tmp)->Montage->CompositeSections.Num();
				}
			}
		}
	}

	return FGameplayAbilitySpecHandle();
}

void UFightComponent::ActiveSkill(FGameplayTag SkillName)
{
	ActiveSkill(SkillName.ToString());
}

void UFightComponent::ActiveSkill(const FString &SkillName)
{
	if(AbilitySystemComponent.IsValid())
	{
		//拿到注册能力的Handle
		if(const FGameplayAbilitySpecHandle *Handle = Skills.Find(FName(SkillName)))
		{
			//用Handle来激活技能
			AbilitySystemComponent->TryActivateAbility(* Handle);
		}
	}
}

void UFightComponent::Hit()
{
	ActiveSkill("Hit");
}

void UFightComponent::Death()
{
	ActiveSkill("Death");
}*/
