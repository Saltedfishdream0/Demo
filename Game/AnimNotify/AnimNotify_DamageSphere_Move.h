// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DamageSphere_Move.generated.h"

class UGameplayEffect;
class ADemoDamageSphere_Move;
/**
 *
 */
UCLASS(meta = (DisplayName = "DamageSphere_Move"))
class DEMO_API UAnimNotify_DamageSphere_Move: public UAnimNotify
{
	GENERATED_BODY()

public:
	//生成的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TSubclassOf<ADemoDamageSphere_Move> DamageSphere_Move;

	//触发的标签
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TSubclassOf<UGameplayEffect> EffectClass;

	//生命周期
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float LifeTime;

	//设置相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FVector RelativeOffsetLocation;

	//设置半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float Radius;

	//设置旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FRotator RotationOffset;


	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;
};
