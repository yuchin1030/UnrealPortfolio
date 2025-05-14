// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	class AChallengersCharacter* player;


	// 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Tutorial;

	// 창 닫기
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	

	// 조작키
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Key;

	UFUNCTION()
	void OnClickKey();


	// 몬스터 커스터마이징
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Mon;

	UFUNCTION()
	void OnClickMon();


	// 던전 커스터마이징
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Dun;

	UFUNCTION()
	void OnClickDun();


	
};
