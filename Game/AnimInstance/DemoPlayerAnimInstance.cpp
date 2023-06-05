// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerAnimInstance.h"

#include "Game/Character/DemoPlayerCharacter.h"

void UDemoPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(ADemoPlayerCharacter *PlayerCharacter = Cast<ADemoPlayerCharacter>(TryGetPawnOwner()))
	{
		bStateSwitch = PlayerCharacter->GetStateSwitch();
	}
}
