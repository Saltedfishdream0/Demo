// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotify/AnimNotify_Potion.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"

FString UAnimNotify_Potion::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Potion::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//目标和煽动者都是自己
	if(MeshComp->GetOwner())
	{
		FGameplayEventData EventData;
		EventData.Instigator = MeshComp->GetOwner();
		EventData.Target     = MeshComp->GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), BuffTags.Last(), EventData);
	}
}
