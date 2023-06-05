// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Game/AI/Component/DemoAIPerceptionComponent.h"
#include "Game/Character/DemoEnemyCharacter.h"

ADemoAIController::ADemoAIController()
{
	DemoPerceptionComponent = CreateDefaultSubobject<UDemoAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(* DemoPerceptionComponent);
}

void ADemoAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AActor *TargetActor = GetFocusOnActor();
	//设置朝向
	SetFocus(TargetActor);
}

void ADemoAIController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);

	ADemoEnemyCharacter *CharacterBase = Cast<ADemoEnemyCharacter>(InPawn);
	if(CharacterBase)
	{
		//指定运行的行为树
		RunBehaviorTree(CharacterBase->GetBehaviorTree());
	}
}

AActor *ADemoAIController::GetFocusOnActor()
{
	if(GetBlackboardComponent())
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}

	return nullptr;
}
