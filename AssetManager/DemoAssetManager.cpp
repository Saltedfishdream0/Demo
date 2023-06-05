// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Game/Item/DemoItem.h"

//静态变量需要初始化声明
const FPrimaryAssetType UDemoAssetManager::PotionItemType    = TEXT("Potion");
const FPrimaryAssetType UDemoAssetManager::TokenItemType     = TEXT("Token");
const FPrimaryAssetType UDemoAssetManager::EquipmentItemType = TEXT("Equipment");

void UDemoAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

UDemoAssetManager &UDemoAssetManager::Get()
{
	UDemoAssetManager *This = Cast<UDemoAssetManager>(GEngine->AssetManager);
	if(This)
	{
		return * This;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("如果未定义资源管理器类名称，则无法使用资源管理器!"));
		return * NewObject<UDemoAssetManager>();
	}
}

UDemoItem *UDemoAssetManager::ForceLoadItem(const FPrimaryAssetId &PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	UDemoItem *LoadedItem = Cast<UDemoItem>(ItemPath.TryLoad());

	if(bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("无法加载标识符的项目 %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
