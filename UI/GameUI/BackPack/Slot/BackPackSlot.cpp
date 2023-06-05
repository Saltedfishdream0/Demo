// Fill out your copyright notice in the Description page of Project Settings.

#include "BackPackSlot.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Component/BackPackComponent.h"
#include "UI/GameUI/BackPack/DragDrog/DemoDragDrog.h"

UBackPackSlot::UBackPackSlot(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBackPackSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &UBackPackSlot::UseMedicines);
}

void UBackPackSlot::UseMedicines()
{
	if(!GetWorld())
	{
		return;
	}

	if(ADemoCharacterBase *CharacterBase = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoCharacterBase>())
	{
		CharacterBase->GetBackPackComponent()->ActiveSkillById(InventoryID);
	}
}

FReply UBackPackSlot::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//判断鼠标是否为右键
	if(InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		FReply Reply = FReply::Handled();

		//获取被按下的控件
		TSharedPtr<SWidget> DragWidget = GetCachedWidget();
		if(DragWidget)
		{
			Reply.DetectDrag(DragWidget.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}

	return FReply::Handled();
}

void UBackPackSlot::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
	if(DragDrogClass && Image && Image->Brush.GetResourceObject())
	{
		//拖动的时候创建一个UDemoDragDrog这个类的控件
		if(UDemoDragDrog *DragDrog = CreateWidget<UDemoDragDrog>(GetWorld(), DragDrogClass))
		{
			//创建一个拖动操作的对象
			if(UDragDropOperation *DragDropOperation = NewObject<UDragDropOperation>(GetTransientPackage(), UDragDropOperation::StaticClass()))
			{
				//需要一个强引用避免GC
				DragDropOperation->SetFlags(RF_StrongRefOnFrame);

				//将本地图像传入UDemoDragDrog这个类控件里面
				DragDrog->DragImage(Cast<UTexture2D>(Image->Brush.GetResourceObject()));

				//定位鼠标的位置渲染
				DragDropOperation->DefaultDragVisual = DragDrog;

				//传入负载信息
				DragDropOperation->Payload = this;

				//把自己的信息赋值过去
				OutOperation = DragDropOperation;

				Num->SetVisibility(ESlateVisibility::Hidden);
				Image->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}


bool UBackPackSlot::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bIsAucceed = false;

	if(InOperation)
	{
		if(ADemoCharacterBase *CharacterBase = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoCharacterBase>())
		{
			//拿到负载的信息
			if(UBackPackSlot *BackPackSlot = Cast<UBackPackSlot>(InOperation->Payload))
			{
				CharacterBase->BackPackSwap(BackPackSlot->InventoryID, InventoryID);

				bIsAucceed = true;
			}
		}
	}

	Num->SetVisibility(ESlateVisibility::HitTestInvisible);
	Image->SetVisibility(ESlateVisibility::HitTestInvisible);

	return bIsAucceed;
}
