// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyCountInDungeonWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UEnemyCountInDungeonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_enemyTotal;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_enemyCur;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_min;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_sec;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Timer;

	UPROPERTY()
	class AOurGameModeBase* gm;

	class AOurGameStateBase* gs;

	// 어떤 버프를 받았는지 알아내는 함수
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_ApplyBuff;

	UFUNCTION()
	void ApplyBuff(int32 BuffNum);

	FText totalText;

	FText curText;

};
