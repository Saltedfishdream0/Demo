// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Game/AI/Component/DemoAIPerceptionComponent.h"
#include "Game/AI/Core/DemoAIController.h"

UBTService_FindEnemy::UBTService_FindEnemy()
{
	NodeName = "Find Enemy";
}

void UBTService_FindEnemy::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	//获取黑板组件
	UBlackboardComponent *Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		ADemoAIController *DemoAIController    = Cast<ADemoAIController>(OwnerComp.GetAIOwner());
		UDemoAIPerceptionComponent *Perception = DemoAIController->GetDemoAIPerceptionComponent();
		if(Perception)
		{
			//将敌人的Key写入黑板
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Perception->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
