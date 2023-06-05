// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/DemoCharacterBase.h"
#include "DemoPlayerCharacter.generated.h"

class UBoxComponent;

//更新MainUI的代理
DECLARE_DELEGATE_OneParam(FUpdateProgressBar, float);

UCLASS(config = Game)
class DEMO_API ADemoPlayerCharacter: public ADemoCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *FollowCamera;

public:
	ADemoPlayerCharacter();

	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	virtual void Tick(float DeltaSeconds) override;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent *GetFollowCamera() const { return FollowCamera; }

private:
	//背部场景武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USceneComponent *Back_Weapon;

	//手部场景武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USceneComponent *Hand_Weapon;

	//武器骨骼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent *Weapon_Mesh;

	//奔跑速度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float RunSpeed;

	//持有武器状态切换
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bStateSwitch;

	//状态切换的蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, meta = (AllowPrivateAccess = "true"))
	UAnimMontage *StateMontage;

	//定时器
	FTimerHandle MonitorTimer;

public:
	//开始跑
	UFUNCTION()
	void SetStartRun();

	//结束跑
	UFUNCTION()
	void SetEndRun();

	//状态切换
	UFUNCTION()
	void StateSwitching();

	//延迟执行切换
	UFUNCTION()
	void CleanTime();

	//开始攻击
	UFUNCTION()
	void BeginComboAttack();

	//结束攻击
	UFUNCTION()
	void EndComboAttack();

	FUpdateProgressBar UpdateHealthProgressBar;
	FUpdateProgressBar UpdateManaProgressBar;
	FUpdateProgressBar UpdateStaminaProgressBar;
	FUpdateProgressBar UpdateExpProgressBar;
	FUpdateProgressBar UpdateLevelText;

	UFUNCTION()
	void UpdateHealth(float Value);
	UFUNCTION()
	void UpdateMana(float Value);
	UFUNCTION()
	void UpdateStamina(float Value);
	UFUNCTION()
	void UpdateExp(float Value);
	UFUNCTION()
	void UpdateLevel(float Value);

	//延迟绑定广播
	UFUNCTION()
	void Update();

	//控制背包
	UFUNCTION()
	void ControlBackPack();

	//控制属性面板
	UFUNCTION()
	void ControlAttributePanel();

	//控制游戏保存和加载面板
	UFUNCTION()
	void ControlSaveAndLoadPanel();

	FORCEINLINE bool GetStateSwitch() { return bStateSwitch; }
};
