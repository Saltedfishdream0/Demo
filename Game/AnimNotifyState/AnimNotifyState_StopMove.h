// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_StopMove.generated.h"

/**
 *
 */
UCLASS(meta = (DisplayName = "StopMove"))
class DEMO_API UAnimNotifyState_StopMove: public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY()
	float NewSpeed;

public:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference) override;
};
