// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DemoCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoCharacterAnimInstance: public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
