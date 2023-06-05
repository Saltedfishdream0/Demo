// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Character/Core/DemoCharacterBase.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	NodeName = "Patrol";
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	AAIController *Contorller            = OwnerComp.GetAIOwner();
	UBlackboardComponent *BlackboardData = OwnerComp.GetBlackboardComponent();

	if(Contorller || BlackboardData)
	{
		if(ADemoCharacterBase *CharacterBase = Contorller->GetPawn<ADemoCharacterBase>())
		{
			//获取最新的信息
			if(UNavigationSystemV1 *NavigationSystem = UNavigationSystemV1::GetCurrent(CharacterBase))
			{
				//在指定范围内随机移动
				FNavLocation NavLocation;

				if(NavigationSystem->GetRandomPointInNavigableRadius(CharacterBase->GetActorLocation(), Range, NavLocation))
				{
					//移动的位置
					BlackboardData->SetValueAsVector(BlackboardKey.SelectedKeyName, NavLocation.Location);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
