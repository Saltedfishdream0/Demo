// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAttributeNum.h"

#include "Components/TextBlock.h"

void UDemoAttributeNum::NativeConstruct()
{
	Super::NativeConstruct();

	Num->SetVisibility(ESlateVisibility::Hidden);
}

void UDemoAttributeNum::SetTextNum(float NewNum)
{
	if(Num)
	{
		Num->SetVisibility(ESlateVisibility::HitTestInvisible);
		FNumberFormattingOptions FormatOptions;
		FormatOptions.SetMinimumFractionalDigits(0);
		FormatOptions.SetMaximumFractionalDigits(0);

		Num->SetText(FText::AsNumber(NewNum, & FormatOptions));
	}
}

void UDemoAttributeNum::SetTextColor(const FLinearColor &Color)
{
	if(Num)
	{
		Num->SetColorAndOpacity(FSlateColor(Color));
	}
}
