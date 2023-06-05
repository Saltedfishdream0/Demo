// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoItem.h"

UDemoItem::UDemoItem()
{
}

bool UDemoItem::IsConsumable() const
{
	if(MaxCount <= 0)
	{
		return true;
	}

	return false;
}

FString UDemoItem::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UDemoItem::GetPrimaryAssetId() const
{
	// 这是一个数据资产，而不是蓝图，因此我们可以只使用原始FName
	// 对于蓝图，您需要处理剥离_C后缀
	return FPrimaryAssetId(ItemType, GetFName());
}
