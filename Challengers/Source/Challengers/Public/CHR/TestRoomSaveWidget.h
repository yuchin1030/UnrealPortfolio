// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestRoomSaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTestRoomSaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

public:
	class AChallengersCharacter* Myplayer = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* SaveYesButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* SaveNoButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UEditableText* InputEnemyName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* showSaveComplete;

	// 플레이어의 현재 소지금 표시
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CurrentGold;

	// 유저가 설정한 몬스터의 총 가격 표시
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CostTotal;

	void CheakLoadedName();

private:
	UFUNCTION()
	void FinalSaveYes();
	UFUNCTION()
	void FinalSaveNo();
};
