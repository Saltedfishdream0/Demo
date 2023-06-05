// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorePanel.generated.h"

class UImage;
class UDemoItem;
class UTextBlock;
class UButton;

//只写了大概的思路没有实现
/**
 *
 */
UCLASS()
class DEMO_API UStorePanel: public UUserWidget
{
	GENERATED_BODY()

	//增加购买的物品
	UPROPERTY(meta = (BindWidget))
	UButton *AddPurchaseItems;

	//减少购买的物品
	UPROPERTY(meta = (BindWidget))
	UButton *DecreasePurchaseItems;

	//确认购买
	UPROPERTY(meta = (BindWidget))
	UButton *ConfirmThePurchase;

	//取消购买
	UPROPERTY(meta = (BindWidget))
	UButton *CancelThePurchase;

	//购买数量的文本
	UPROPERTY(meta = (BindWidget))
	UTextBlock *PurchaseQuantity;

	//购买物品的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = "true"))
	UDemoItem *DemoItemPtr;

	//购买物品的图像
	UPROPERTY(meta = (BindWidget))
	UImage *GoodsImage;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	//增加数量的函数
	UFUNCTION()
	void AddPurchaseItemsFun();

	//减少数量的函数
	UFUNCTION()
	void DecreasePurchaseItemsFun();

	//确认购买的函数
	UFUNCTION()
	void ConfirmThePurchaseFun();

	//取消购买的函数
	UFUNCTION()
	void CancelThePurchaseFun();

	//默认购买的数量
	UPROPERTY()
	int32 NumberOfItems = 0;

	//购买的数量显示
	void PurchaseQuantityFun(int32 Value);
};
