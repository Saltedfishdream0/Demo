// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetManager/DemoAssetManager.h"
#include "Game/Item/DemoItem.h"
#include "DemoEquipment.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoEquipment: public UDemoItem
{
	GENERATED_BODY()

public:
	UDemoEquipment() { ItemType = UDemoAssetManager::EquipmentItemType; }
};
