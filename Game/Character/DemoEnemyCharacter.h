// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/DemoCharacterBase.h"
#include "DemoEnemyCharacter.generated.h"

class UGameplayEffect;
class UBehaviorTree;

UCLASS()
class DEMO_API ADemoEnemyCharacter: public ADemoCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree *DemoBehaviorTree;

public:
	// Sets default values for this character's properties
	ADemoEnemyCharacter();

	FORCEINLINE UBehaviorTree *GetBehaviorTree() { return DemoBehaviorTree; }

	virtual void Death() override;

	//定时器
	FTimerHandle MonitorTimer;

	//延迟销毁
	UFUNCTION()
	void DelayedDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//指定敌人提供的经验
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Exp, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> EffectClass;

	//改变经验
	void ExpChanged();
};
