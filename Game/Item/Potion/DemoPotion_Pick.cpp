// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPotion_Pick.h"

#include "Components/SphereComponent.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Game/Component/BackPackComponent.h"


// Sets default values
ADemoPotion_Pick::ADemoPotion_Pick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent   = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ADemoPotion_Pick::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADemoPotion_Pick::OnComponentBeginOverlap);
}

void ADemoPotion_Pick::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//仅玩家可拾取
	if(ADemoPlayerCharacter *PlayerCharacter = Cast<ADemoPlayerCharacter>(OtherActor))
	{
		//防止重复添加
		if(!bActive)
		{
			FDemoBackPackItem PackItem;
			PackItem.DemoItem  = ItemType;
			PackItem.ItemCount = Count;

			//添加进背包
			PlayerCharacter->GetBackPackComponent()->AddBackPack(PackItem);

			bActive = true;

			Destroy();
		}
	}
}
