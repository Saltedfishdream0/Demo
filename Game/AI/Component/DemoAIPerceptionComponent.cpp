// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAIPerceptionComponent.h"

#include "AIController.h"
#include "Game/Ability/AttributeSet/DemoAttributeSet.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "Perception/AISense_Sight.h"

AActor *UDemoAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PerceiveActors;

	//获取感知到的Acotr
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if(PerceiveActors.Num() != 0)
	{
		if(AAIController *Contorller = Cast<AAIController>(GetOwner()))
		{
			APawn *Pawn = Contorller->GetPawn();

			float BestDistance = MAX_FLT;

			AActor *BasePawn = nullptr;

			//遍历感知到的Acotr
			for(auto &PerActor : PerceiveActors)
			{
				//TODO 这里写基类可以让敌人互相伤害, 写成玩家则只攻击玩家
				ADemoPlayerCharacter *CharacterBase = Cast<ADemoPlayerCharacter>(PerActor);
				if(CharacterBase && CharacterBase->GetAttributeSet()->GetHealth() > 0)
				{
					//变更距离
					float CurrentDistance = (PerActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
					if(CurrentDistance < BestDistance)
					{
						BestDistance = CurrentDistance;
						BasePawn     = PerActor;
					}
				}
			}

			return BasePawn;
		}
	}

	return nullptr;
}
