// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DamageBox.h"

#include "Game/DamageActor/DemoDamageBox.h"

UAnimNotify_DamageBox::UAnimNotify_DamageBox()
{
}

FString UAnimNotify_DamageBox::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_DamageBox::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	Super::Notify(MeshComp, Animation);

	if(AActor *InActor = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector Location  = MeshComp->GetSocketLocation(SockName);
		FRotator Rotation = MeshComp->GetSocketRotation(SockName);
		//欧拉角转换成四元数
		FTransform Transform((Rotation + RotationOffset).Quaternion(), Location);

		//延迟生成
		if(ADemoDamageBox *DamageBox = InActor->GetWorld()->SpawnActorDeferred<ADemoDamageBox>(
			DemoBox,
			Transform,
			nullptr,
			Cast<APawn>(InActor),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
		{
			//激活的目标
			DamageBox->SetBuffs(BuffTags);
			DamageBox->SetDamageBoxExtent(BoxExtent);

			DamageBox->SetLifeSpan(LifeTime);

			//设置位置
			FVector RelativeLocation = DamageBox->GetDamageBox()->GetRelativeLocation();
			DamageBox->SetDamageBoxRelativeLocation(RelativeLocation + RelativeOffsetLocation);

			//结束延迟生成
			DamageBox->FinishSpawning(Transform);

			//生成后绑定,否则会失败
			if(bBind)
			{
				DamageBox->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SockName);
			}
		}
	}
}
