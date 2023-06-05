// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoEnemyCharacter.h"

#include "DemoPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/AI/Core/DemoAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADemoEnemyCharacter::ADemoEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ADemoAIController::StaticClass();

	//改善AI旋转不自然
	bUseControllerRotationYaw                             = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate                  = FRotator(0.f, 200.f, 0.f);
}

void ADemoEnemyCharacter::Death()
{
	Super::Death();

	AAIController *AIController = Cast<AAIController>(Controller);
	if(AIController)
	{
		//解除当前AI的控制
		AIController->UnPossess();
	}

	if(!GetWorld())
	{
		return;
	}

	ExpChanged();

	//关闭胶囊体碰撞
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//血条不可见
	GetBloorBar()->SetVisibility(false);


	GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, & ADemoEnemyCharacter::DelayedDestruction, 10.f, false);
}

void ADemoEnemyCharacter::DelayedDestruction()
{
	GetWorld()->GetTimerManager().ClearTimer(MonitorTimer);

	Destroy();
}

// Called when the game starts or when spawned
void ADemoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADemoEnemyCharacter::ExpChanged()
{
	//改变玩家的经验
	ADemoPlayerCharacter *Target = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoPlayerCharacter>();
	if(!Target)
	{
		return;
	}

	//拿到GAS
	if(UAbilitySystemComponent *InAbilitySystemComponent = Target->GetAbilitySystemComponent())
	{
		//创建一个上下文
		FGameplayEffectContextHandle EffectContext = InAbilitySystemComponent->MakeEffectContext();
		//给上下文添加一个源目标
		EffectContext.AddSourceObject(Target);
		//创建一个实例GE,并得到它的Handle
		//GE的类,等级(默认参数用来查询等级不同造成不同的效果)
		FGameplayEffectSpecHandle EffectSpecHandle = InAbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);

		if(EffectSpecHandle.IsValid())
		{
			//应用实例到目标
			InAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(* EffectSpecHandle.Data.Get(), InAbilitySystemComponent);
		}
	}
}
