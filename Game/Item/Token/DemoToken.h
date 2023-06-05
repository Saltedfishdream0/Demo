// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetManager/DemoAssetManager.h"
#include "Game/Item/DemoItem.h"
#include "DemoToken.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoToken: public UDemoItem
{
	GENERATED_BODY()

public:
	UDemoToken() { ItemType = UDemoAssetManager::TokenItemType; }
};
