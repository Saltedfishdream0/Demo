// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DemoAssetManager.generated.h"

class UDemoItem;
/**
 *
 */
UCLASS()
class DEMO_API UDemoAssetManager: public UAssetManager
{
	GENERATED_BODY()

public:
	UDemoAssetManager()
	{
	}

	virtual void StartInitialLoading() override;

	/** 返回当前资产管理器对象 */
	static UDemoAssetManager &Get();

	//定义的方法
	static const FPrimaryAssetType PotionItemType;
	static const FPrimaryAssetType TokenItemType;
	static const FPrimaryAssetType EquipmentItemType;

	/**
 * 同步加载 Item 子类，这可能会卡住，但当您无法等待异步加载时很有用 这不会维护对项目的引用，因此如果没有以其他方式加载，它将进行垃圾回收
 *
 * @param PrimaryAssetId 要加载的资产标识符
 * @param bDisplayWarning 如果为 true，则在项目加载失败时将记录警告
 */
	UDemoItem *ForceLoadItem(const FPrimaryAssetId &PrimaryAssetId, bool bLogWarning = true);
};
