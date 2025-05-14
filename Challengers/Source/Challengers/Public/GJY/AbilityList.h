// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Blueprint/IUserObjectListEntry.h>
#include "AbilityList.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UAbilityList : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	class UWeapon1Object* WO;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextCoolDown;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextDuration;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextWeight;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextCost;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextName;

	
	UFUNCTION()
	void ClickSelectButton();


	class ABaseEnemy* Enemy;

	FName Ability;
};
