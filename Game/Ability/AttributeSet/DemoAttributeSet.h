// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Game/DataTable/CharacterData.h"
#include "DemoAttributeSet.generated.h"

#define PROPERTY_FUNCTION_REGISTRATION(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class DEMO_API UDemoAttributeSet: public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Defense)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Exp)
	FGameplayAttributeData Exp;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Exp)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxExp)
	FGameplayAttributeData MaxExp;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, MaxExp)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	PROPERTY_FUNCTION_REGISTRATION(UDemoAttributeSet, Damage)

	UDemoAttributeSet();

	//预处理
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData &Data) override;

	//处理完成
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override;

	//同步数据表
	UFUNCTION(BlueprintCallable)
	virtual void RegistrationProperties(const FCharacterData &InData);

	//注册
	void RegistrationParam(FGameplayAttributeData &InAttributeData, const float InValue);

	//掌管属性同步规则
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	//属性修改后的回调函数
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Exp(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_MaxExp(const FGameplayAttributeData &OldValue);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData &OldValue);
};
