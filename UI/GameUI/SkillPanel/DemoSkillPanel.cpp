// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoSkillPanel.h"

#include "Abilities/GameplayAbility.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Slot/DemoSkillSlot.h"

void UDemoSkillPanel::NativeConstruct()
{
	Super::NativeConstruct();

	InitSkill();

	if(!GetWorld())
	{
		return;
	}

	if(APlayerController *PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>())
	{
		if(ADemoCharacterBase *CharacterBase = PlayerController->GetPawn<ADemoCharacterBase>())
		{
			CharacterBase->UpdateCoolDown.BindUObject(this, &UDemoSkillPanel::UpdateCoolDown);
		}
	}
}

void UDemoSkillPanel::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDemoSkillPanel::InitSkill()
{
	if(!GetWorld())
	{
		return;
	}

	if(SKillSlotClass)
	{
		if(ADemoCharacterBase *CharacterBase = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoCharacterBase>())
		{
			if(ADemoGameStateBase *StateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
			{
				//获取玩家ID
				int32 ID = CharacterBase->GetCharacterID();

				//获取对应ID的所有技能信息
				TArray<FSkillData*> SkillDatas = StateBase->GetSkillDataTable(ID);

				int32 j = 0;

				for(size_t i = 0; i < 6; i++)
				{
					//创建技能格子
					if(UDemoSkillSlot *SkillSlot = CreateWidget<UDemoSkillSlot>(GetWorld(), SKillSlotClass))
					{
						//将技能格子添加进水平框
						if(UHorizontalBoxSlot *BoxSlot = SkillArray->AddChildToHorizontalBox(SkillSlot))
						{
							if(SkillDatas.Num() > 0)
							{
								for(; j < SkillDatas.Num(); j++)
								{
									if(UGameplayAbility *Ability = Cast<UGameplayAbility>(SkillDatas[j]->GameplayAbility.GetDefaultObject()))
									{
										FString Tag = Ability->AbilityTags.ToStringSimple();

										//排除不需要的标签,寻找下一个GA
										if(Tag == "ComboAttack")
										{
											continue;
										}
									}

									//把主动技能更新进技能槽
									SkillSlot->Update(* SkillDatas[j]);
									j++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void UDemoSkillPanel::UpdateCoolDown(const FName &Name, float Value)
{
	//拿到技能的CD
	auto Tmp = [&](UDemoSkillSlot *SkillSlot)
	{
		if(SkillSlot)
		{
			if(SkillSlot->Tags == Name)
			{
				SkillSlot->GetCD(Value);
				SkillSlot->GetMaxCD(Value);

				return true;
			}
		}

		return false;
	};

	if(SkillArray)
	{
		//循环遍历子项,把每一个Slot传入执行更新
		for(int32 i =0;i<SkillArray->GetChildrenCount();i++)
		{
			if(Tmp(Cast<UDemoSkillSlot>(SkillArray->GetChildAt(i))))
			{
				break;
			}
		}
	}
}
