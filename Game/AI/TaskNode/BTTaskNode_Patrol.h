// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UBTTaskNode_Patrol: public UBTTaskNode
{
	GENERATED_BODY()

	//黑版选择器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector BlackboardKey;

	//移动的范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float Range;

public:
	UBTTaskNode_Patrol();

	/** 启动此任务，应返回成功，失败或正在进行（返回正在进行时使用FinishLatentTask（）如果节点未实例化，则此函数应被视为常量（不要修改对象的状态）！*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
