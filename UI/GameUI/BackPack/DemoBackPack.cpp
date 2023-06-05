// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoBackPack.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Item/DemoItem.h"

UDemoBackPack::UDemoBackPack(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDemoBackPack::NativeConstruct()
{
	Super::NativeConstruct();

	InitBackpack();

	if(APlayerController *PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>())
	{
		if(ADemoCharacterBase *CharacterBase = PlayerController->GetPawn<ADemoCharacterBase>())
		{
			CharacterBase->GetBackPackComponent()->OnBackPackChangedNative.BindUFunction(this, "OnBackPackSlot");
		}
	}
}

void UDemoBackPack::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDemoBackPack::InitBackpack()
{
	if(!BackPackSlotClass)
	{
		return;
	}

	if(BackPackSlotPanel->GetChildrenCount() == 0)
	{
		for(size_t i = 0; i < 5; i++)
		{
			for(size_t j = 0; j < 6; j++)
			{
				if(UBackPackSlot *BackPackSlot = CreateWidget<UBackPackSlot>(GetWorld(), BackPackSlotClass))
				{
					//对应数组元素
					BackPackSlot->InventoryID = i * 6 + j;
					//设置列
					if(UUniformGridSlot *GridSlot = BackPackSlotPanel->AddChildToUniformGrid(BackPackSlot, i, j))
					{
						GridSlot->SetHorizontalAlignment(HAlign_Fill);
						GridSlot->SetVerticalAlignment(VAlign_Fill);
					}
				}
			}
		}
	}
}

void UDemoBackPack::OnBackPackSlot(TArray<FDemoBackPackItem> DemoBackPackClass)
{
	if(DemoBackPackClass.Num() > 0)
	{
		for(size_t i = 0; i < 5; i++)
		{
			for(size_t j = 0; j < 6; j++)
			{
				//遍历数组
				if(UBackPackSlot *BackPackSlot = Cast<UBackPackSlot>(BackPackSlotPanel->GetChildAt(i * 6 + j)))
				{
					//查看数组是否有数据
					if(DemoBackPackClass[i * 6 + j].IsNull())
					{
						BackPackSlot->GetNum()->SetText(FText::FromString(FString::FromInt(DemoBackPackClass[i * 6 + j].ItemCount)));
						BackPackSlot->GetNum()->SetVisibility(ESlateVisibility::Visible);

						BackPackSlot->GetImage()->SetBrushFromTexture(DemoBackPackClass[i * 6 + j].DemoItem->ItemIcon);
						BackPackSlot->GetImage()->SetVisibility(ESlateVisibility::Visible);
					}
					else
					{
						BackPackSlot->GetNum()->SetVisibility(ESlateVisibility::Hidden);

						BackPackSlot->GetImage()->SetVisibility(ESlateVisibility::Hidden);
						BackPackSlot->GetImage()->SetBrushResourceObject(nullptr);
					}
				}
			}
		}
	}
}

/*void UDemoBackPack::OnBackPackSlot(int32 ColumNum, int32 RowNum)
{
	if(BackPackSlotClass)
	{
		for(int32 Row = 0; Row < RowNum; Row++)
		{
			for(int32 Colum = 0; Colum < ColumNum; Colum++)
			{
				UBackPackSlot *PackSlot = CreateWidget<UBackPackSlot>(GetWorld(), BackPackSlotClass);
				if(PackSlot)
				{
					//将目标添加进UniformGridSlot
					UUniformGridSlot *GridSlot = BackPackSlotArray->AddChildToUniformGrid(PackSlot);
					if(GridSlot)
					{
						GridSlot->SetColumn(Colum);
						GridSlot->SetRow(Row);
						GridSlot->SetHorizontalAlignment(HAlign_Fill);
						GridSlot->SetVerticalAlignment(VAlign_Fill);
					}

					BackPackSlots.Add(PackSlot);
				}
			}
		}
	}
}*/
