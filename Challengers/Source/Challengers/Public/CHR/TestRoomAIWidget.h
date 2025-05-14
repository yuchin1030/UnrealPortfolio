// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHR/BaseEnemy.h"
#include "TestRoomAIWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTestRoomAIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	void NativeConstruct() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* BattleDistSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* RandomAreaSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* MoveRateSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* PlayerFindDistSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* TargetChangeRateSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* Phase2RateSlide;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class USlider* Phase3RateSlide;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* AISaveBtn;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* AICancelBtn;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_1;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_2;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_3;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_4;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_5;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_6;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_7;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_1;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_2;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_3;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_4;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_5;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_6;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_7;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* showSaveComplete;

	class ATestRoomGameMode* TRGM = nullptr;

	struct FAIStat newAIData;//AI데이터 구조체

	UFUNCTION()
	void OnHovered1();

	UFUNCTION()
	void OnUnhovered1();

	UFUNCTION()
	void OnHovered2();

	UFUNCTION()
	void OnUnhovered2();

	UFUNCTION()
	void OnHovered3();

	UFUNCTION()
	void OnUnhovered3();

	UFUNCTION()
	void OnHovered4();

	UFUNCTION()
	void OnUnhovered4();

	UFUNCTION()
	void OnHovered5();

	UFUNCTION()
	void OnUnhovered5();

	UFUNCTION()
	void OnHovered6();

	UFUNCTION()
	void OnUnhovered6();

	UFUNCTION()
	void OnHovered7();

	UFUNCTION()
	void OnUnhovered7();

	UFUNCTION()
	void ClickSaveButton();

	UFUNCTION()
	void ClickCancelButton();
};
