// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DemoAIController.generated.h"

class UDemoAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoAIController: public AAIController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIComponent, meta = (AllowPrivateAccess = "true"))
	UDemoAIPerceptionComponent *DemoPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIComponent, meta = (AllowPrivateAccess = "true"))
	FName FocusOnKeyName = "EnemyActor";

public:
	ADemoAIController();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UDemoAIPerceptionComponent *GetDemoAIPerceptionComponent() { return DemoPerceptionComponent; }

protected:
	virtual void OnPossess(APawn *InPawn) override;

	AActor *GetFocusOnActor();
};
