// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonClearFailWidget.generated.h"


UCLASS()
class UDungeonClearFailWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	// Panel ¿¬°á
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_DungeonClearFail;


	// º¸»ó¹Þ±â ¹öÆ°
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_GetItem;

	UFUNCTION()
	void OnClickGetItem();



	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimArrow;




// 	// È¹µæ °ñµå·®
// 	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
// 	class UTextBlock* TextBlock_GetGold;
// 
// 	UFUNCTION()
// 	void GetGoldPlayer();
// 
// 
// 
// 	// È¹µæ °æÇèÄ¡
// 	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
// 	class UTextBlock* TextBlock_getEXP;
// 
// 	UFUNCTION();
// 	void GetEXPPlayer();

};
