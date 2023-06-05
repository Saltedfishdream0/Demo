// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DamageSphere_Move.h"

#include "Game/DamageActor/DemoDamageSphere_Move.h"

FString UAnimNotify_DamageSphere_Move::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_DamageSphere_Move::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	Super::Notify(MeshComp, Animation);

	if(AActor *InActor = Cast<AActor>(MeshComp->GetOuter()))
	{
		auto Vector = InActor->GetActorForwardVector();

		FTransform Transform(Vector);

		//延迟生成
		if(ADemoDamageSphere_Move *DamageSphere = InActor->GetWorld()->SpawnActorDeferred<ADemoDamageSphere_Move>
			(DamageSphere_Move,
			 Transform,
			 nullptr,
			 Cast<APawn>(InActor),
			 ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				))
		{
			//激活的GE
			DamageSphere->SetGameplayEffect(EffectClass);

			//初始化目标
			DamageSphere->SetInitSpeed(InActor);

			//设置生命周期
			DamageSphere->SetLifeSpan(LifeTime);

			FVector Location = InActor->GetActorLocation();

			//设置位置
			DamageSphere->SetLocation(Location);

			DamageSphere->FinishSpawning(Transform);
		}
	}
}
