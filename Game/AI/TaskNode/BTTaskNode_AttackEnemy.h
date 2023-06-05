// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_AttackEnemy.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UBTTaskNode_AttackEnemy: public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector EnemyActorKey;

public:

	UBTTaskNode_AttackEnemy();

	/** 启动此任务，应返回成功，失败或正在进行（返回正在进行时使用FinishLatentTask（）如果节点未实例化，则此函数应被视为常量（不要修改对象的状态）！*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
