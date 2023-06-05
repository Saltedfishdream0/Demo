// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_AttackEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Character/Core/DemoCharacterBase.h"

UBTTaskNode_AttackEnemy::UBTTaskNode_AttackEnemy()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTaskNode_AttackEnemy::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	//return Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController *Contorller        = OwnerComp.GetAIOwner();
	UBlackboardComponent *Blackboard = OwnerComp.GetBlackboardComponent();

	bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Contorller)
	{
		ADemoCharacterBase *CharacterBase = Contorller->GetPawn<ADemoCharacterBase>();
		//有目标激活能力
		if(HasAim)
		{
			CharacterBase->ActiveSkillByString("Enemy.Attack");

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
