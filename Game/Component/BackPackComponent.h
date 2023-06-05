// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackPackComponent.generated.h"

class UDemoBackPack;
class UDemoItem;

USTRUCT(BlueprintType)
struct FDemoBackPackItem
{
	GENERATED_USTRUCT_BODY()

	FDemoBackPackItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackPack)
	UDemoItem *DemoItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackPack)
	int32 ItemCount;

	bool IsNull();

	void ResetSelf();
};

class ADemoCharacterBase;
class UDemoAbilitySystemComponent;

//通知背包UI的代理
DECLARE_DELEGATE_OneParam(FOnBackPackChangedNative, TArray<FDemoBackPackItem>);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEMO_API UBackPackComponent: public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<ADemoCharacterBase> DemoCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UDemoAbilitySystemComponent> AbilitySystemComponent;

public:
	// Sets default values for this component's properties
	UBackPackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//保存背包数据的数组
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BackPack)
	TArray<FDemoBackPackItem> BackPackArray;

public:
	FORCEINLINE TArray<FDemoBackPackItem> &GetBackPackArray() { return BackPackArray; }

	//增加数量
	UFUNCTION(BlueprintCallable, Category = BackPack)
	bool AddBackPack(FDemoBackPackItem NewItem);

	UFUNCTION()
	void AddBackPackArray(TArray<FDemoBackPackItem> NewItem);

	//移除数组元素
	UFUNCTION()
	void RemoveBackPack(int32 Idex);

	//移除具体对象
	UFUNCTION()
	void RemoveBackPackByItem(FDemoBackPackItem NewItem);

	//交换
	UFUNCTION()
	void SwapBackPack(int32 Index_i, int32 Index_j);

	//通知UI刷新界面
	UFUNCTION()
	void BackPackChanged(const TArray<FDemoBackPackItem> &BackPackItems);

	FOnBackPackChangedNative OnBackPackChangedNative;

	//按照ID激活能力
	UFUNCTION()
	void ActiveSkillById(int32 MedicinesID);
};
