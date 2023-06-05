// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoDamageSphere_Move.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Game/Ability/DemoAbilitySystemComponent.h"
#include "Game/Character/Core/DemoCharacterBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADemoDamageSphere_Move::ADemoDamageSphere_Move()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent   = SphereComponent;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Niagara");
	NiagaraComponent->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

// Called when the game starts or when spawned
void ADemoDamageSphere_Move::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADemoDamageSphere_Move::ComponentBeginOverlap);
}

void ADemoDamageSphere_Move::ComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(GetInstigator() != OtherActor)
	{
		if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(GetInstigator()))
		{
			if(ADemoCharacterBase *Target = Cast<ADemoCharacterBase>(OtherActor))
			{
				//生成特效的类
				if(!bIsSpawn)
				{
					AActor *NewActor = GetWorld()->SpawnActor<AActor>(NiagaraActor, Target->GetActorLocation(), FRotator::ZeroRotator);

					bIsSpawn = true;
				}

				//命中后更改球体半径
				SphereComponent->SetSphereRadius(DamageRadius);

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

				Destroy();
			}
		}
	}
}

void ADemoDamageSphere_Move::SetLife(float Value)
{
	SetLifeSpan(Value);
}

void ADemoDamageSphere_Move::SetRadius(float Value)
{
	SphereComponent->SetSphereRadius(Value);
}

void ADemoDamageSphere_Move::SetLocation(const FVector Value)
{
	SphereComponent->SetRelativeLocation(Value);
}

void ADemoDamageSphere_Move::SetInitSpeed(AActor *Actor)
{
	if(Actor)
	{
		FVector Vector = Actor->GetActorForwardVector();

		ProjectileMovementComponent->Velocity = Vector * ProjectileMovementComponent->InitialSpeed;
	}
}
