// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "DemoDamageBox.generated.h"

class ADemoCharacterBase;
class UBoxComponent;

UCLASS(Blueprintable, BlueprintType)
class DEMO_API ADemoDamageBox: public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent *SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent *DamageBox;

public:
	// Sets default values for this actor's properties
	ADemoDamageBox();

	//设置碰撞事件
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//设置GAS的标签
	void SetBuffs(const TArray<FGameplayTagContainer> &InBuffs) { BuffTags = InBuffs; }

	UPrimitiveComponent *GetDamageBox();

	//设置盒体的大小
	void SetDamageBoxExtent(const FVector &InVector);

	//设置盒体的位置
	void SetDamageBoxRelativeLocation(const FVector &InVector);

	//判断当前目标是否已经受到攻击
	bool IsExist(ACharacter *NewTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FGameplayTagContainer> BuffTags;

	//存储重叠目标
	UPROPERTY()
	TArray<TWeakObjectPtr<ADemoCharacterBase>> AttackedTarget;
};
