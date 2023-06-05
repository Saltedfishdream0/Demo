// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "DemoDamageSphere_Move.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;
class UNiagaraComponent;
class USphereComponent;

UCLASS()
class DEMO_API ADemoDamageSphere_Move: public AActor
{
	GENERATED_BODY()

	//碰撞球体
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent *SphereComponent;

	//特效
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent *NiagaraComponent;

	//发射物移动组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovementComponent;

	//命中后的半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageRadius", meta = (AllowPrivateAccess = "true"))
	float DamageRadius;

	//指定生成的类(特效)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NiagaraActor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> NiagaraActor;

	//判断是否已经生成过
	UPROPERTY()
	bool bIsSpawn;

public:
	// Sets default values for this actor's properties
	ADemoDamageSphere_Move();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//指定需要的GE
	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;

public:
	//设置碰撞事件
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//设置生命周期
	void SetLife(float Value);

	//设置半径
	void SetRadius(float Value);

	//设置生成的位置
	void SetLocation(const FVector Value);

	//设置GAS的标签
	void SetGameplayEffect(TSubclassOf<UGameplayEffect> &InGE) { EffectClass = InGE; }

	//设置生成的位置
	void SetInitSpeed(AActor *Actor);
};
