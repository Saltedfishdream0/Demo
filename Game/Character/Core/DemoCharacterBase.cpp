// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacterBase.h"


#include "DataRegistrySubsystem.h"
#include "Components/WidgetComponent.h"
#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/Ability/DemoGameplayAbility.h"
#include "Game/Ability/AttributeSet/DemoAttributeSet.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Component/BackPackComponent.h"
#include "Game/Component/FightComponent.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "UI/GameUI/AttributeNum/DemoAttributeNum.h"
#include "UI/GameUI/BloodBar/DemoBloodBar.h"

// Sets default values
ADemoCharacterBase::ADemoCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UDemoAbilitySystemComponent>("AbilitySystemComponent");

	//属性
	AttributeSet = CreateDefaultSubobject<UDemoAttributeSet>("AttributeSet");

	//血条组件
	BloorBar = CreateDefaultSubobject<UWidgetComponent>("BloorComponent");
	BloorBar->SetupAttachment(RootComponent);
	BloorBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//背包组件
	BackPacksComponent = CreateDefaultSubobject<UBackPackComponent>("BackPackComponent");

	//战斗组件
	FightComponent = CreateDefaultSubobject<UFightComponent>("FightComponent");

	//属性变换时的载体
	AttributeNum = CreateDefaultSubobject<UWidgetComponent>("AttributeNum");
	AttributeNum->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADemoCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//注册GAS
	if(AbilitySystemComponent && GetLocalRole() == ROLE_Authority)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	if(UGameInstance *GameInstance = GetGameInstance())
	{
		//获取到数据注册表
		if(UDataRegistrySubsystem *DataRegistrySubsystem = GameInstance->GetEngine()->GetEngineSubsystem<UDataRegistrySubsystem>())
		{
			//读取配置的数据表
			const FCharacterData *Data = DataRegistrySubsystem->GetCachedItem<FCharacterData>(DataRegistryId);

			if(Data)
			{
				//注册属性
				AttributeSet->RegistrationProperties(* Data);
			}
		}
	}

	//读表注册能力
	if(ADemoGameStateBase *GameStateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
	{
		TArray<UGameplayAbility*> SkillsAbilities = GameStateBase->GetSkills(CharacterID);

		RegisterGameAbility(SkillsAbilities);
	}

	//更新血条
	UpdateHealthBar(AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
}

// Called every frame
void ADemoCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoCharacterBase::UpdateHealthBar(float HealthPercent)
{
	if(BloorBar)
	{
		if(UDemoBloodBar *Blood = Cast<UDemoBloodBar>(BloorBar->GetUserWidgetObject()))
		{
			Blood->SetBloodPercent(HealthPercent);
		}
	}
}

void ADemoCharacterBase::SpawAttributeNum(float Value, const FLinearColor &Color)
{
	//float NewNum = Value;
	if(UDemoAttributeNum *AttributeNumClass = Cast<UDemoAttributeNum>(AttributeNum->GetUserWidgetObject()))
	{
		AttributeNum->SetWidget(AttributeNumClass);

		AttributeNumClass->SetTextNum(Value);
		AttributeNumClass->SetTextColor(Color);
	}
}

FGameplayAbilitySpecHandle ADemoCharacterBase::RegisterGameAbility(TArray<UGameplayAbility*> InAbility)
{
	if(GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		if(AbilitySystemComponent && InAbility.Num() > 0)
		{
			for(auto &Tmp : InAbility)
			{
				//调用系统注册能力,返回一个Handle
				FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Tmp));

				//拿到技能的Tag
				const FString String = Tmp->AbilityTags.ToStringSimple();

				//转换到FName存入TMap
				Skills.Add(FName(String), Handle);

				//注册普通攻击连击
				if(String.Equals("Player.ComboAttack"))
				{
					FightComponent->GetComboAttack()->PlayerCharacter = Cast<ADemoPlayerCharacter>(GetOuter());
					FightComponent->GetComboAttack()->ComboKey        = "Player.ComboAttack";
					FightComponent->GetComboAttack()->MaxIndex        = Cast<UDemoGameplayAbility>(Tmp)->Montage->CompositeSections.Num();
				}
			}
		}
	}

	return FGameplayAbilitySpecHandle();
}

void ADemoCharacterBase::ActiveSkill(FGameplayTag SkillName)
{
	ActiveSkillByString(SkillName.ToString());
}

void ADemoCharacterBase::ActiveSkillByString(const FString &SkillName)
{
	if(AbilitySystemComponent)
	{
		//拿到注册能力的Handle
		if(const FGameplayAbilitySpecHandle *Handle = Skills.Find(FName(SkillName)))
		{
			//用Handle来激活技能
			AbilitySystemComponent->TryActivateAbility(* Handle);
		}
	}
}

void ADemoCharacterBase::Hit()
{
	ActiveSkillByString("Hit");
}

void ADemoCharacterBase::Death()
{
	ActiveSkillByString("Death");
}

void ADemoCharacterBase::BackPackSwap(int32 Index_i, int32 Index_j)
{
	BackPacksComponent->SwapBackPack(Index_i, Index_j);
}

void ADemoCharacterBase::UpdateCD(const FName &Name, float Value)
{
	UpdateCoolDown.ExecuteIfBound(Name, Value);
}
