// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Potion.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Potion"))
class DEMO_API UAnimNotify_Potion: public UAnimNotify
{
	GENERATED_BODY()

public:
	//触发的Tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	FGameplayTagContainer BuffTags;

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference) override;
};
