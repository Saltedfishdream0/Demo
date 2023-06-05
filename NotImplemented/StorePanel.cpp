// Fill out your copyright notice in the Description page of Project Settings.


#include "StorePanel.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Component/BackPackComponent.h"
#include "Game/Item/DemoItem.h"

void UStorePanel::NativeConstruct()
{
	Super::NativeConstruct();

	AddPurchaseItems->OnClicked.AddDynamic(this, &UStorePanel::AddPurchaseItemsFun);
	DecreasePurchaseItems->OnClicked.AddDynamic(this, &UStorePanel::DecreasePurchaseItemsFun);
	ConfirmThePurchase->OnClicked.AddDynamic(this, &UStorePanel::ConfirmThePurchaseFun);
	CancelThePurchase->OnClicked.AddDynamic(this, &UStorePanel::CancelThePurchaseFun);


	GoodsImage->SetBrushFromTexture(DemoItemPtr->ItemIcon);
}

void UStorePanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStorePanel::AddPurchaseItemsFun()
{
	NumberOfItems++;

	PurchaseQuantityFun(NumberOfItems);
}

void UStorePanel::DecreasePurchaseItemsFun()
{
	NumberOfItems--;
	if(NumberOfItems < 0)
	{
		NumberOfItems = 0;
	}

	PurchaseQuantityFun(NumberOfItems);
}

void UStorePanel::ConfirmThePurchaseFun()
{
	if(ADemoPlayerCharacter *PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoPlayerCharacter>())
	{
		FDemoBackPackItem BackPackItem;
		BackPackItem.ItemCount = NumberOfItems;
		BackPackItem.DemoItem  = DemoItemPtr;

		PlayerCharacter->GetBackPackComponent()->AddBackPack(BackPackItem);
	}
}

void UStorePanel::CancelThePurchaseFun()
{
	//关闭面板

	NumberOfItems = 0;
}

void UStorePanel::PurchaseQuantityFun(int32 Value)
{
	PurchaseQuantity->SetText(FText::AsNumber(NumberOfItems));
}
