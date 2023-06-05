// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogUI.generated.h"

class UDemoGameContinue;
class UDemoGameSetting;
class UButton;
/**
 * 
 */
UCLASS()
class DEMO_API ULogUI: public UUserWidget
{
	GENERATED_BODY()

	//开始游戏
	UPROPERTY(meta = (BindWidget))
	UButton *Start;

	//读取存档
	UPROPERTY(meta = (BindWidget))
	UButton *Continue;

	//设置
	UPROPERTY(meta = (BindWidget))
	UButton *Settings;

	//退出
	UPROPERTY(meta = (BindWidget))
	UButton *Exit;

	//设置面板
	UPROPERTY(meta = (BindWidget))
	UDemoGameSetting *GameSettingPanel;

	//存档面板
	UPROPERTY(meta = (BindWidget))
	UDemoGameContinue *GameContinuePanel;

public:
	ULogUI(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void BeginGame();

	UFUNCTION()
	void OpenArchive();

	UFUNCTION()
	void OpenSetting();

	UFUNCTION()
	void ExitGame();
};
