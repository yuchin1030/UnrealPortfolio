// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Blueprint/IUserObjectListEntry.h>
#include "WeaponList2.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UWeaponList2 : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()


public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	class UWeapon1Object* WO;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RangeText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CostText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeightText;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Text;

	UFUNCTION()
	void ClickSelectButton();
	
	class ABaseEnemy* Enemy;

	FName Weapon;
	
};
