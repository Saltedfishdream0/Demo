// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetManager/DemoAssetManager.h"
#include "Game/Item/DemoItem.h"
#include "DemoPotion.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoPotion: public UDemoItem
{
	GENERATED_BODY()

public:
	UDemoPotion() { ItemType = UDemoAssetManager::PotionItemType; }
};
