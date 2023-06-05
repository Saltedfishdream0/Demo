// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DamageActor/DemoDamageBox.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "Game/Character/Core/DemoCharacterBase.h"

// Sets default values
ADemoDamageBox::ADemoDamageBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent  = SceneComponent;

	DamageBox = CreateDefaultSubobject<UBoxComponent>("DamageBox");
	DamageBox->SetupAttachment(SceneComponent);
}

void ADemoDamageBox::ComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//首先排除自己
	if(GetInstigator() != OtherActor)
	{
		//把自己转换成人物类
		if(ADemoCharacterBase *CharacterBase = Cast<ADemoCharacterBase>(GetInstigator()))
		{
			//把目标转换成人物类
			if(ADemoCharacterBase *InTarget = Cast<ADemoCharacterBase>(OtherActor))
			{
				//传给GAS事件的数据 把煽动者和目标传入
				FGameplayEventData EventData;
				EventData.Instigator = GetInstigator();
				EventData.Target     = InTarget;

				if(IsExist(InTarget))
				{
					return;
				}

				if(!BuffTags.IsEmpty())
				{
					for(auto &Tmp : BuffTags)
					{
						UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), Tmp.Last(), EventData);
					}
					//标记已处理
					AttackedTarget.AddUnique(InTarget);

					//Destroyed();
				}
			}
		}
	}
}

UPrimitiveComponent *ADemoDamageBox::GetDamageBox()
{
	return DamageBox;
}

void ADemoDamageBox::SetDamageBoxExtent(const FVector &InVector)
{
	DamageBox->SetBoxExtent(InVector);
}

void ADemoDamageBox::SetDamageBoxRelativeLocation(const FVector &InVector)
{
	if(UPrimitiveComponent *PrimitiveComponent = GetDamageBox())
	{
		PrimitiveComponent->SetRelativeLocation(InVector);
	}
}

// Called when the game starts or when spawned
void ADemoDamageBox::BeginPlay()
{
	Super::BeginPlay();

	if(UPrimitiveComponent *PrimitiveComponent = GetDamageBox())
	{
		//游戏中隐藏
		PrimitiveComponent->SetHiddenInGame(true);
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ADemoDamageBox::ComponentBeginOverlap);
	}
}

bool ADemoDamageBox::IsExist(ACharacter *NewTarget)
{
	for(auto &Tmp : AttackedTarget)
	{
		if(Tmp.IsValid())
		{
			if(Tmp == NewTarget)
			{
				return true;
			}
		}
	}

	return false;
}
