// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Component/BackPackComponent.h"

#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/Ability/DemoGameplayAbility.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Item/DemoItem.h"

FDemoBackPackItem::FDemoBackPackItem() :
	DemoItem(nullptr),
	ItemCount(0)
{
}

bool FDemoBackPackItem::IsNull()
{
	if(DemoItem && ItemCount > 0)
	{
		return true;
	}

	return false;
}

void FDemoBackPackItem::ResetSelf()
{
	DemoItem  = nullptr;
	ItemCount = 0;
}

// Sets default values for this component's properties
UBackPackComponent::UBackPackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UBackPackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	DemoCharacter = Cast<ADemoCharacterBase>(GetOwner());

	if(DemoCharacter.IsValid())
	{
		AbilitySystemComponent = Cast<UDemoAbilitySystemComponent>(DemoCharacter->GetAbilitySystemComponent());
	}

	//初始化仓库
	if(BackPackArray.Num() == 0)
	{
		for(size_t i = 0; i < 30; i++)
		{
			BackPackArray.Add(FDemoBackPackItem());
		}
	}
}

bool UBackPackComponent::AddBackPack(FDemoBackPackItem NewItem)
{
	if(GetOwner()->GetLocalRole() != ROLE_Authority)
	{
		return false;
	}

	if(!NewItem.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Vail!"));

		return false;
	}

	//遍历背包里面有没有,有就在原先基础上增加
	for(size_t i = 0; i < BackPackArray.Num(); i++)
	{
		if(BackPackArray[i].DemoItem == NewItem.DemoItem)
		{
			if(NewItem.DemoItem->MaxCount > 1)
			{
				BackPackArray[i].ItemCount += NewItem.ItemCount;

				BackPackChanged(BackPackArray);

				return true;
			}
		}
	}

	//遍历背包有没有空的位置
	for(size_t i = 0; i < BackPackArray.Num(); i++)
	{
		if(!BackPackArray[i].DemoItem)
		{
			BackPackArray[i] = NewItem;

			BackPackChanged(BackPackArray);

			return true;
		}
	}

	//仓库满了
	return false;
}

void UBackPackComponent::AddBackPackArray(TArray<FDemoBackPackItem> NewItem)
{
	for(size_t i = 0; i < NewItem.Num(); i++)
	{
		BackPackArray[i] = NewItem[i];

		BackPackChanged(BackPackArray);
	}
}

void UBackPackComponent::RemoveBackPack(int32 Idex)
{
	BackPackArray[Idex].ResetSelf();
	/**/
	BackPackChanged(BackPackArray);
}

void UBackPackComponent::RemoveBackPackByItem(FDemoBackPackItem NewItem)
{
	for(size_t i = 0; i < BackPackArray.Num(); i++)
	{
		if(BackPackArray[i].DemoItem == NewItem.DemoItem)
		{
			//减去目标的数量
			BackPackArray[i].ItemCount -= NewItem.ItemCount;

			if(BackPackArray[i].ItemCount <= 0)
			{
				BackPackArray[i].ResetSelf();
			}

			BackPackChanged(BackPackArray);

			break;
		}
	}
}

void UBackPackComponent::SwapBackPack(int32 Index_i, int32 Index_j)
{
	BackPackArray.Swap(Index_i, Index_j);

	BackPackChanged(BackPackArray);
}

void UBackPackComponent::BackPackChanged(const TArray<FDemoBackPackItem> &BackPackItems)
{
	OnBackPackChangedNative.ExecuteIfBound(BackPackItems);
}

void UBackPackComponent::ActiveSkillById(int32 MedicinesID)
{
	if(BackPackArray[MedicinesID].IsNull())
	{
		//授予能力
		UDemoGameplayAbility *GameplayAbility = Cast<UDemoGameplayAbility>(BackPackArray[MedicinesID].DemoItem->GrantedAbility.GetDefaultObject());

		//给予能力
		FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GameplayAbility));

		//尝试激活能力
		AbilitySystemComponent->TryActivateAbility(Handle);

		//自动移除Handle
		AbilitySystemComponent->SetRemoveAbilityOnEnd(Handle);
	}
}
