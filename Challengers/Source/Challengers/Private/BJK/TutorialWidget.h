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


	// ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Tutorial;

	// â �ݱ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	

	// ����Ű
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Key;

	UFUNCTION()
	void OnClickKey();


	// ���� Ŀ���͸���¡
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Mon;

	UFUNCTION()
	void OnClickMon();


	// ���� Ŀ���͸���¡
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Dun;

	UFUNCTION()
	void OnClickDun();


	
};
