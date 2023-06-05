// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DamageBox.generated.h"

class ADemoDamageBox;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DamageBox_AnimNotify"))
class DEMO_API UAnimNotify_DamageBox: public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_DamageBox();

	//获取通知的名字
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

	//生成的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TSubclassOf<ADemoDamageBox> DemoBox;

	//触发的Tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TArray<FGameplayTagContainer> BuffTags;

	//生命周期
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float LifeTime;

	//绑定的骨骼名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FName SockName;

	//判断固定生成还是可以随人物移动
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	bool bBind;

	//设置旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FRotator RotationOffset;

	//设置大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FVector BoxExtent;

	//设置相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FVector RelativeOffsetLocation;
};
