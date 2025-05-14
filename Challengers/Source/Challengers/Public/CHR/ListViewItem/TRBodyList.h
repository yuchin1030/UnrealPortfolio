// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Blueprint/IUserObjectListEntry.h>
#include "TRBodyList.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTRBodyList : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	class UWeapon1Object* WO;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* NameText;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* HPText;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* WeightText;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CostText;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextBlock_true;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Type_Boss;
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Type_Mon;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;
	
	UFUNCTION()
	void ClickSelectButton();

	FName Body;

	int32 indexNum;
};