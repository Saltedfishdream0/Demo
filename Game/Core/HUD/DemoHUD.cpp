// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/GameUI/GameMainUI.h"

ADemoHUD::ADemoHUD()
{
	static ConstructorHelpers::FClassFinder<UGameMainUI> UI_GameMainClass(TEXT("/Game/UI/GameUI/UI_GameMain"));
	GameMainUIClass = UI_GameMainClass.Class;
}

void ADemoHUD::BeginPlay()
{
	Super::BeginPlay();

	if(GameMainUIClass)
	{
		GameUI = CreateWidget<UGameMainUI>(GetWorld(), GameMainUIClass);

		GameUI->AddToViewport();
	}
}
