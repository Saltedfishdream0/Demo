// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboAttack.h"

#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Component/FightComponent.h"

void UAnimNotify_ComboAttack::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(MeshComp->GetOuter()))
	{
		//结束动画的时候没有触发,连击置为空
		CharacterBase->GetFightComponents()->GetComboAttack()->EndAnimation();
	}
}
