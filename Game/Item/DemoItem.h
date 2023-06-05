// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DemoItem.generated.h"

class UDemoGameplayAbility;
/**
 *
 */
/* 所有项的基类，不要直接蓝图 */
UCLASS()
class DEMO_API UDemoItem: public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//Type of this item, set in native parent class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	// 用户可见的短名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	// 用户可见的长描述
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	// 要显示的图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	UTexture2D *ItemIcon;

	// 游戏中的价格
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 Price;

	//一次可以在清单中的最大实例数，<=0 表示无限
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxCount;

	/** 此项目的最大等级，<= 0 表示无限 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxLevel;

	// Ability to grant if this item is slotted
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TSubclassOf<UDemoGameplayAbility> GrantedAbility;

	// 此物品授予的能力等级。<= 0 表示字符级别
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	int32 AbilityLevel;

	UDemoItem();

	// 如果项目是易耗品，则返回（最大计数 <= 0）
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
	bool IsConsumable() const;

	//返回逻辑名称，等效于主资产 ID
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	// 重写以使用保存的类型
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
