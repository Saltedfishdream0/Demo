// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMainUI.h"

#include "AttributePanel/DemoAttributePanel.h"
#include "BackPack/DemoBackPack.h"
#include "BackPack/Slot/BackPackSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/Character/DemoPlayerCharacter.h"
#include "Blueprint/DragDropOperation.h"
#include "Kismet/GameplayStatics.h"
#include "SaveAndLoad/DemoSaveAndLoad.h"

UGameMainUI::UGameMainUI(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Player->UpdateHealthProgressBar.BindUObject(this, & UGameMainUI::UpdateHealthProgressBar);
		Player->UpdateManaProgressBar.BindUObject(this, & UGameMainUI::UpdateManaProgressBar);
		Player->UpdateStaminaProgressBar.BindUObject(this, & UGameMainUI::UpdateStaminaProgressBar);
		Player->UpdateExpProgressBar.BindUObject(this, & UGameMainUI::UpdateExpProgressBar);
		Player->UpdateLevelText.BindUObject(this, & UGameMainUI::UpdateLevelProgressBar);
	}

	//背包和鼠标默认隐藏
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	BackPackClass->SetVisibility(ESlateVisibility::Hidden);

	//属性面板默认隐藏
	AttributePanel->SetVisibility(ESlateVisibility::Hidden);

	//读取和保存面板默认隐藏
	SaveAndLoadPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UGameMainUI::NativeDestruct()
{
	Super::NativeDestruct();

	//TODO 解绑会崩溃,好像也不太需要解除,不清楚,后面再说
	/*if(ADemoPlayerCharacter *Player = Cast<ADemoPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Player->UpdateHealthProgressBar.Unbind();
		Player->UpdateManaProgressBar.Unbind();
		Player->UpdateStaminaProgressBar.Unbind();
		Player->UpdateExpProgressBar.Unbind();
		Player->UpdateLevelText.Unbind();
	}*/
}

void UGameMainUI::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//更新面板,逐帧减少
	if(HealthBar && !FMath::IsNearlyEqual(TargetHealth, HealthBar->Percent))
	{
		double NewValue = FMath::FInterpTo(HealthBar->Percent, TargetHealth, InDeltaTime, 3.0);

		HealthBar->SetPercent(NewValue);
	}

	if(ManaBar && !FMath::IsNearlyEqual(TargetMana, ManaBar->Percent))
	{
		double NewValue = FMath::FInterpTo(ManaBar->Percent, TargetMana, InDeltaTime, 3.0);

		ManaBar->SetPercent(NewValue);
	}

	if(StaminaBar && !FMath::IsNearlyEqual(TargetStamina, StaminaBar->Percent))
	{
		double NewValue = FMath::FInterpTo(StaminaBar->Percent, TargetStamina, InDeltaTime, 3.0);

		StaminaBar->SetPercent(NewValue);
	}

	if(ExpBar && !FMath::IsNearlyEqual(TargetExp, ExpBar->Percent))
	{
		double NewValue = FMath::FInterpTo(ExpBar->Percent, TargetExp, InDeltaTime, 3.0);

		ExpBar->SetPercent(NewValue);
	}
}

void UGameMainUI::UpdateHealthProgressBar(float Value)
{
	TargetHealth = Value;
}

void UGameMainUI::UpdateManaProgressBar(float Value)
{
	TargetMana = Value;
}

void UGameMainUI::UpdateStaminaProgressBar(float Value)
{
	TargetStamina = Value;
}

void UGameMainUI::UpdateExpProgressBar(float Value)
{
	TargetExp = Value;
}

void UGameMainUI::UpdateLevelProgressBar(float Value)
{
	FNumberFormattingOptions FormatOptions;
	FormatOptions.SetMinimumFractionalDigits(0);
	FormatOptions.SetMaximumFractionalDigits(0);

	LevelText->SetText(FText::AsNumber(Value, & FormatOptions));
}

bool UGameMainUI::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bIsAucceed = false;

	//如果拖到主UI上面显示
	if(InOperation)
	{
		if(ADemoCharacterBase *CharacterBase = GetWorld()->GetFirstPlayerController()->GetPawn<ADemoCharacterBase>())
		{
			//拿到负载的信息
			if(UBackPackSlot *BackPackSlot = Cast<UBackPackSlot>(InOperation->Payload))
			{
				BackPackSlot->GetNum()->SetVisibility(ESlateVisibility::HitTestInvisible);
				BackPackSlot->GetImage()->SetVisibility(ESlateVisibility::HitTestInvisible);

				bIsAucceed = true;
			}
		}
	}


	return bIsAucceed;
}

void UGameMainUI::ShowAndHideBackPack()
{
	if(!GetWorld())
	{
		return;
	}

	if(BackPackClass)
	{
		ESlateVisibility SlateVisibility = BackPackClass->GetVisibility();
		if(SlateVisibility == ESlateVisibility::Visible)
		{
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
			BackPackClass->SetVisibility(ESlateVisibility::Hidden);
			GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(false);
		}
		else
		{
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
			BackPackClass->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(true);
		}
	}
}

void UGameMainUI::ShowAndHideAttributePanel()
{
	if(!GetWorld())
	{
		return;
	}

	if(AttributePanel)
	{
		ESlateVisibility SlateVisibility = AttributePanel->GetVisibility();
		if(SlateVisibility == ESlateVisibility::Visible)
		{
			AttributePanel->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			AttributePanel->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UGameMainUI::ShowAndHideSaveAndLoadPanel()
{
	if(!GetWorld())
	{
		return;
	}

	if(SaveAndLoadPanel)
	{

		ESlateVisibility SlateVisibility = SaveAndLoadPanel->GetVisibility();
		if(SlateVisibility == ESlateVisibility::Visible)
		{
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

			SaveAndLoadPanel->SetVisibility(ESlateVisibility::Hidden);

			//用全局时间膨胀代替暂停游戏
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);

			//锁定玩家视角
			GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(false);
		}
		else
		{
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

			SaveAndLoadPanel->SetVisibility(ESlateVisibility::Visible);

			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
			GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(true);
		}
	}
}
