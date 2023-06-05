// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoBloodBar.h"

#include "Components/ProgressBar.h"

void UDemoBloodBar::SetBloodPercent(float Value)
{
	BloodBar->SetPercent(Value);
}
