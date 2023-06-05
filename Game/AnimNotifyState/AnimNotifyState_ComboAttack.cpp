// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ComboAttack.h"

#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Game/Component/FightComponent.h"

void UAnimNotifyState_ComboAttack::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if(ADemoPlayerCharacter *CharacterBase = Cast<ADemoPlayerCharacter>(MeshComp->GetOuter()))
		{
			//消耗连击,短按置为false
			CharacterBase->GetFightComponents()->GetComboAttack()->bShorPressed = false;

			//播放下一个动画
			CharacterBase->GetFightComponents()->GetComboAttack()->AnimationIndex();
		}
	}
}

void UAnimNotifyState_ComboAttack::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_ComboAttack::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if(ADemoPlayerCharacter *CharacterBase = Cast<ADemoPlayerCharacter>(MeshComp->GetOuter()))
		{
			if(CharacterBase->GetFightComponents()->GetComboAttack()->bLongPressed || CharacterBase->GetFightComponents()->GetComboAttack()->bShorPressed)
			{
				CharacterBase->ActiveSkillByString("Player.ComboAttack");
			}
		}
	}
}
