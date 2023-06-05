// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoDragDrog.h"

#include "Components/Image.h"

void UDemoDragDrog::DragImage(UTexture2D *InImage)
{
	Image->SetBrushFromTexture(InImage);
}
