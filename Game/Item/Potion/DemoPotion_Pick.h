// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoPotion_Pick.generated.h"

class UDemoItem;
class UWidgetComponent;
class USphereComponent;
class UCapsuleComponent;

UCLASS()
class DEMO_API ADemoPotion_Pick: public AActor
{
	GENERATED_BODY()

	//药品的球形碰撞
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent *SphereComponent;

	//药品的骨骼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MeshComponent;

	//所属的资产类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Potion, meta = (AllowPrivateAccess = "true"))
	UDemoItem *ItemType;

	//一个物品的数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Potion, meta = (AllowPrivateAccess = "true"))
	int32 Count;

	UPROPERTY()
	bool bActive;

public:
	// Sets default values for this actor's properties
	ADemoPotion_Pick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
