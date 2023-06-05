// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "DemoAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoAIPerceptionComponent: public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief 遍历所有目标查询,发现目标后改变距离
	 * @return 返回当前目标
	 */
	AActor *GetClosestEnemy();
};
