// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveDungeonData.h"
#include "DungeonListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UDungeonListWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_enemySelect;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_Remove;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonNameText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonTypeText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* dungeonCostText;

	int32 dunIndex;

	UPROPERTY()
    FString _dunName;

    UPROPERTY()
    FString _dunType;

	 UPROPERTY()
    TArray<FObjectSaveData> _savedEnemys;

	UPROPERTY()
	class ADungeonEditCharacter* dc;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectAnim;


	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnHovered();

	UFUNCTION()
	void LoadDungeon();

	UFUNCTION()
	void RemoveDungeon(FString __dunName);

	UFUNCTION()
	void QuestionRemove();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Select;

	bool Select2 = false;

	class UDungeonEditWidget* EW;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
