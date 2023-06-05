// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AttackEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Character/Core/DemoCharacterBase.h"

UBTService_AttackEnemy::UBTService_AttackEnemy()
{
	NodeName = "AttackEnemy";
}

void UBTService_AttackEnemy::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
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
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
