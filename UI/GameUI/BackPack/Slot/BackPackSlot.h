// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BackPackSlot.generated.h"

class UButton;
class UDemoDragDrog;
class UImage;
class UTextBlock;
/**
 *
 */
UCLASS()
class DEMO_API UBackPackSlot: public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Num;

	UPROPERTY(meta = (BindWidget))
	UImage *Image;

	UPROPERTY(meta = (BindWidget))
	UButton *SlotButton;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UDemoDragDrog> DragDrogClass;

public:
	UBackPackSlot(const FObjectInitializer &ObjectInitializer);
	virtual void NativeConstruct() override;

	//标识对应仓库的数组
	UPROPERTY()
	int32 InventoryID;

	virtual FReply NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;

	FORCEINLINE UTextBlock *GetNum() { return Num; }
	FORCEINLINE UImage *GetImage() { return Image; }

	//使用药品
	UFUNCTION()
	void UseMedicines();

};
