// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/Character.h"
#include "DemoCharacterBase.generated.h"

class UGameplayAbility;
class UDemoAttributeSet;
class UDemoAbilitySystemComponent;
class UFightComponent;
class UBackPackComponent;
class UWidgetComponent;

//更新CD的代理
DECLARE_DELEGATE_TwoParams(FUpdateCoolDown, const FName&, float);

UCLASS()
class DEMO_API ADemoCharacterBase: public ACharacter
{
	GENERATED_BODY()

protected:
	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDemoAbilitySystemComponent> AbilitySystemComponent;

	//属性集
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDemoAttributeSet> AttributeSet;

	//血条控件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent *BloorBar;

	//属性组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBackPackComponent> BackPacksComponent;

	//属性变化的数字
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent *AttributeNum;

	//战斗组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFightComponent> FightComponent;

	//角色ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta=(AllowPrivateAccess = "true"))
	int32 CharacterID;

	//必须把Handle放在TMap里面,不然找不到
	UPROPERTY()
	TMap<FName, FGameplayAbilitySpecHandle> Skills;

	//配置的基础属性表
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	FDataRegistryId DataRegistryId;

public:
	//注册能力
	FGameplayAbilitySpecHandle RegisterGameAbility(TArray<UGameplayAbility*> InAbility);

	//激活技能
	UFUNCTION(BlueprintCallable)
	void ActiveSkill(FGameplayTag SkillName);
	UFUNCTION()
	void ActiveSkillByString(const FString &SkillName);

	FUpdateCoolDown UpdateCoolDown;
	//更新CD
	UFUNCTION()
	void UpdateCD(const FName &Name, float Value);

public:
	// Sets default values for this character's properties
	ADemoCharacterBase();

	FORCEINLINE UDemoAbilitySystemComponent *GetAbilitySystemComponent() { return AbilitySystemComponent; }
	FORCEINLINE UBackPackComponent *GetBackPackComponent() { return BackPacksComponent; }
	FORCEINLINE UFightComponent *GetFightComponents() { return FightComponent; }
	FORCEINLINE int32 GetCharacterID() { return CharacterID; }
	FORCEINLINE UDemoAttributeSet *GetAttributeSet() { return AttributeSet; }
	FORCEINLINE UWidgetComponent *GetBloorBar() { return BloorBar; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateHealthBar(float HealthPercent);

	//数值生成
	UFUNCTION()
	void SpawAttributeNum(float Value, const FLinearColor &Color);

	void Hit();
	virtual void Death();

	//背包交换
	void BackPackSwap(int32 Index_i, int32 Index_j);
};
