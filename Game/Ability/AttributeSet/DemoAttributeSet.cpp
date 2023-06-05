// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/DataTable/CharacterData.h"
#include "Net/UnrealNetwork.h"

UDemoAttributeSet::UDemoAttributeSet()
{
}

bool UDemoAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData &Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UDemoAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data)
{
	Super::PostGameplayEffectExecute(Data);

	//属性改变后的工作
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	//拿到发起者的ASC
	UAbilitySystemComponent *Soure          = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer &SourceTags = * Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;

	if(Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	//拿到目标的ASC  没有发起者会崩溃
	AActor *TargetActor                 = nullptr;
	AController *TargetController       = nullptr;
	ADemoCharacterBase *TargetCharacter = nullptr;

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor      = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter  = Cast<ADemoCharacterBase>(TargetActor);
	}

	//处理属性变化信息
	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if(Soure && TargetCharacter)
		{
			const UDemoAttributeSet *SourceAttr = Cast<UDemoAttributeSet>(Soure->GetAttributeSet(StaticClass()));
			const UDemoAttributeSet *TargetAttr = Cast<UDemoAttributeSet>(TargetCharacter->GetAbilitySystemComponent()->GetAttributeSet(StaticClass()));

			if(GetHealth() < 0)
			{
				return;
			}

			//伤害计算
			float NewAttack     = SourceAttr->GetAttack();
			float TargetDefense = GetDefense();
			float NewDamage     = GetDamage() + NewAttack - TargetDefense;
			float NewHealth     = FMath::Clamp(GetHealth() - NewDamage, 0.f, GetMaxHealth());

			//更新属性
			SetHealth(NewHealth);

			//更新头顶的UI(敌人)
			TargetCharacter->UpdateHealthBar(GetHealth() / GetMaxHealth());

			//玩家更新面板
			if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
			{
				Player->UpdateHealth(GetHealth() / GetMaxHealth());
			}

			//判断当前生命值,小于等于0就死亡
			if(GetHealth() <= 0)
			{
				TargetCharacter->Death();
			}
			//否则播放受击
			if(GetHealth() > 0)
			{
				TargetCharacter->Hit();
			}

			//生成属性变化数字
			TargetCharacter->SpawAttributeNum(- NewDamage, FLinearColor::Red);
			SetDamage(0.f);
		}
	}
	else if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if(TargetCharacter)
		{
			//更新头顶血条
			TargetCharacter->UpdateHealthBar(GetHealth() / GetMaxHealth());

			if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
			{
				Player->UpdateHealth(GetHealth() / GetMaxHealth());
			}

			//判断当前生命值,小于等于0就死亡
			/*if(GetHealth() <= 0.f)
			{
				TargetCharacter->Death();
			}*/

			//否则播放受击
			/*if(GetHealth() > 0)
			{
				TargetCharacter->Hit();
			}*/

			//生成属性变化数字
			if(DeltaValue != 0)
			{
				if(DeltaValue > 0)
				{
					TargetCharacter->SpawAttributeNum(DeltaValue, FLinearColor::Green);
				}
				else
				{
					TargetCharacter->SpawAttributeNum(DeltaValue, FLinearColor::Red);
				}
			}
		}
	}

	else if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));

		if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
		{
			Player->UpdateMana(GetMana() / GetMaxMana());
		}

		if(DeltaValue != 0)
		{
			TargetCharacter->SpawAttributeNum(DeltaValue, FLinearColor::Blue);
		}
	}

	else if(Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));

		if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
		{
			Player->UpdateStamina(GetStamina() / GetMaxStamina());
		}
	}

	else if(Data.EvaluatedData.Attribute == GetExpAttribute())
	{
		//SetExp(FMath::Clamp(GetExp(), 0.f, GetMaxExp()));
		if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
		{
			//经验满了升级  查询经验是否溢出
			if(GetExp() == GetMaxExp() || GetExp() > GetMaxExp())
			{
				//保存溢出的经验
				float NewExp = GetExp() - GetMaxExp();
				//当前经验归0
				SetExp(NewExp);
				//等级+1
				float NewLevel = GetLevel() + 1;
				//改变等级属性
				SetLevel(NewLevel);
				//更新等级
				Player->UpdateLevel(GetLevel());

				const FCharacterData InData;
				//升级后的属性变化
				float NewNum = GetMaxHealth() + InData.AddHealth;
				SetMaxHealth(NewNum);
				SetHealth(NewNum);

				NewNum = GetMaxMana() + InData.AddMana;
				SetMaxMana(NewNum);
				SetMana(NewNum);

				NewNum = GetMaxExp() + InData.AddExp;
				SetMaxExp(NewNum);

				NewNum = GetAttack() + InData.AddAttack;
				SetAttack(NewNum);

				//更新
				Player->UpdateHealth(GetHealth() / GetMaxHealth());
				Player->UpdateMana(GetMana() / GetMaxMana());
				Player->UpdateStamina(GetStamina() / GetMaxStamina());
			}
			Player->UpdateExp(GetExp() / GetMaxExp());
		}

		if(DeltaValue != 0)
		{
			TargetCharacter->SpawAttributeNum(DeltaValue, FLinearColor::Yellow);
		}
	}

	else if(Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(TargetCharacter))
		{
			//升级之后的属性变化
			SetLevel(GetLevel() + 1);
			Player->UpdateLevel(GetLevel());

			const FCharacterData InData;

			float NewNum = GetMaxHealth() + InData.AddHealth;
			SetMaxHealth(NewNum);
			SetHealth(NewNum);

			NewNum = GetMaxMana() + InData.AddMana;
			SetMaxMana(NewNum);
			SetMana(NewNum);

			NewNum = GetMaxExp() + InData.AddExp;
			SetMaxExp(NewNum);

			NewNum = GetAttack() + InData.AddAttack;
			SetAttack(NewNum);
		}
	}
}

void UDemoAttributeSet::RegistrationProperties(const FCharacterData &InData)
{
	//注册数据
	RegistrationParam(Level, InData.Level);

	RegistrationParam(Health, InData.Health);
	RegistrationParam(MaxHealth, InData.MaxHealth);

	RegistrationParam(Mana, InData.Mana);
	RegistrationParam(MaxMana, InData.MaxMana);

	RegistrationParam(Stamina, InData.Stamina);
	RegistrationParam(MaxStamina, InData.MaxStamina);

	RegistrationParam(Attack, InData.Attack);

	RegistrationParam(Defense, InData.Defense);

	RegistrationParam(Exp, InData.Exp);
	RegistrationParam(MaxExp, InData.MaxExp);
}

void UDemoAttributeSet::RegistrationParam(FGameplayAttributeData &InAttributeData, const float InValue)
{
	InAttributeData.SetBaseValue(InValue);
	InAttributeData.SetCurrentValue(InValue);
}

void UDemoAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDemoAttributeSet, Level);

	DOREPLIFETIME(UDemoAttributeSet, Health);
	DOREPLIFETIME(UDemoAttributeSet, MaxHealth);

	DOREPLIFETIME(UDemoAttributeSet, Mana);
	DOREPLIFETIME(UDemoAttributeSet, MaxMana);

	DOREPLIFETIME(UDemoAttributeSet, Stamina);
	DOREPLIFETIME(UDemoAttributeSet, MaxStamina);

	DOREPLIFETIME(UDemoAttributeSet, Attack);
	DOREPLIFETIME(UDemoAttributeSet, Defense);

	DOREPLIFETIME(UDemoAttributeSet, Exp);
	DOREPLIFETIME(UDemoAttributeSet, MaxExp);

	DOREPLIFETIME(UDemoAttributeSet, Damage);
}

void UDemoAttributeSet::OnRep_Level(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Level, OldValue);
}

void UDemoAttributeSet::OnRep_Health(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Health, OldValue);
}

void UDemoAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxHealth, OldValue);
}

void UDemoAttributeSet::OnRep_Mana(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Mana, OldValue);
}

void UDemoAttributeSet::OnRep_MaxMana(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxMana, OldValue);
}

void UDemoAttributeSet::OnRep_Stamina(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Stamina, OldValue);
}

void UDemoAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxStamina, OldValue);
}

void UDemoAttributeSet::OnRep_Attack(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Attack, OldValue);
}

void UDemoAttributeSet::OnRep_Defense(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Defense, OldValue);
}

void UDemoAttributeSet::OnRep_Exp(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Exp, OldValue);
}

void UDemoAttributeSet::OnRep_MaxExp(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxExp, OldValue);
}

void UDemoAttributeSet::OnRep_Damage(const FGameplayAttributeData &OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Damage, OldValue);
}
