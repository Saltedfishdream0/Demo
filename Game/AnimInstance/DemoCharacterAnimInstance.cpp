// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacterAnimInstance.h"

#include "Game/Character/Core/DemoCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDemoCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(TryGetPawnOwner()))
	{
		if(UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(CharacterBase->GetMovementComponent()))
		{
			if(MovementComponent->IsFalling())
			{
				bIsFalling = true;
			}
			else
			{
				bIsFalling = false;
			}

			FVector InVector = CharacterBase->GetVelocity();
			Speed            = InVector.Size();
		}
	}
}
