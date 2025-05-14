// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveToDungeonWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UMoveToDungeonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_MoveToDungeon;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_close;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* CloseAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* StartAnim;
	
	UFUNCTION()
	void MoveToDungeon();

	UFUNCTION()
	void MoveToDungeon_Ho();

	UFUNCTION()
	void MoveToDungeon_Unho();

	UFUNCTION()
	void CloseWidget();

	UFUNCTION()
	void CloseWidget_Ho();

	UFUNCTION()
	void CloseWidget_Unho();
};
