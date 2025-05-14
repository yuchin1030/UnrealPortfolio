// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveDungeonData.h"
#include "CreateRoomDungeonListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UCreateRoomDungeonListWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;


public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_createDungeon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonNameText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonTypeText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonCostText;


	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* ClickAnim;

	int32 dunIndex;

	UPROPERTY()
    FString _dunName;

    UPROPERTY()
    FString _dunType;

	UPROPERTY()
	int32 _dunCost;

	 UPROPERTY()
    TArray<FObjectSaveData> _savedEnemys;

	UPROPERTY()
	class ADungeonEditCharacter* dc;

	UFUNCTION()
	void SendDungeonName();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnHovered();

	bool Show=false;
	
};
