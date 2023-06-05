// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacterAnimInstance.h"
#include "DemoPlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoPlayerAnimInstance: public UDemoCharacterAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	bool bStateSwitch;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
