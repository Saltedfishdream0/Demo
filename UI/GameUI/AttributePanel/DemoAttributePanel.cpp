// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAttributePanel.h"

#include "Components/TextBlock.h"
#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/Ability/AttributeSet/DemoAttributeSet.h"
#include "Game/Character/DemoPlayerCharacter.h"

void UDemoAttributePanel::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(GetWorld())
	{
		//获取到玩家
		ADemoPlayerCharacter *PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoPlayerCharacter>();
		//拿到GAS
		if(UDemoAbilitySystemComponent *ASC = PlayerCharacter->GetAbilitySystemComponent())
		{
			//拿到属性集
			if(const UDemoAttributeSet *Attributes = Cast<UDemoAttributeSet>(ASC->GetAttributeSet(UDemoAttributeSet::StaticClass())))
			{
				//定义3个变量
				FString TmpString;
				float Num;
				float MaxNum;

				//等级
				if(LeveText)
				{
					Num = Attributes->GetLevel();

					//使用前需要清空缓冲区
					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));

					// 在设置控件文本时，获取 FString 缓存的 const TCHAR* 指针，并将其传递给 FText 构造函数
					LeveText->SetText(FText::FromString(TmpString.operator*()));
				}

				//经验
				if(ExpText)
				{
					Num    = Attributes->GetExp();
					MaxNum = Attributes->GetMaxExp();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));
					TmpString.Append(TEXT("/"));
					TmpString.Append(FString::SanitizeFloat(MaxNum));

					ExpText->SetText(FText::FromString(TmpString.operator*()));
				}

				//生命
				if(HealthText)
				{
					Num    = Attributes->GetHealth();
					MaxNum = Attributes->GetMaxHealth();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));
					TmpString.Append(TEXT("/"));
					TmpString.Append(FString::SanitizeFloat(MaxNum));

					HealthText->SetText(FText::FromString(TmpString.operator*()));
				}

				//魔法
				if(ManaText)
				{
					Num    = Attributes->GetMana();
					MaxNum = Attributes->GetMaxMana();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));
					TmpString.Append(TEXT("/"));
					TmpString.Append(FString::SanitizeFloat(MaxNum));

					ManaText->SetText(FText::FromString(TmpString.operator*()));
				}

				//耐力
				if(StaminaText)
				{
					Num    = Attributes->GetStamina();
					MaxNum = Attributes->GetMaxStamina();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));
					TmpString.Append(TEXT("/"));
					TmpString.Append(FString::SanitizeFloat(MaxNum));

					StaminaText->SetText(FText::FromString(TmpString.operator*()));
				}

				//攻击
				if(AttackText)
				{
					Num = Attributes->GetAttack();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));

					AttackText->SetText(FText::FromString(TmpString.operator*()));
				}

				//防御
				if(DefenseText)
				{
					Num = Attributes->GetDefense();

					TmpString.Reset();
					TmpString.Append(FString::SanitizeFloat(Num));

					DefenseText->SetText(FText::FromString(TmpString.operator*()));
				}
			}
		}
	}
}
