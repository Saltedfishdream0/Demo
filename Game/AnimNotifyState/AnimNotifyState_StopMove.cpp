// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StopMove.h"

#include "Game/Character/Core/DemoCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UAnimNotifyState_StopMove::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotifyState_StopMove::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(MeshComp->GetOwner()))
	{
		NewSpeed                                            = CharacterBase->GetCharacterMovement()->MaxAcceleration;
		CharacterBase->GetCharacterMovement()->MaxAcceleration = 0.f;
	}
}

void UAnimNotifyState_StopMove::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(MeshComp->GetOwner()))
	{
		CharacterBase->GetCharacterMovement()->MaxAcceleration = NewSpeed;
	}

}
