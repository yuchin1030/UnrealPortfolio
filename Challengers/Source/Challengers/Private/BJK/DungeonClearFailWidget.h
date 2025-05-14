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

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_DungeonClearFail;


	// ����ޱ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_GetItem;

	UFUNCTION()
	void OnClickGetItem();



	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimArrow;




// 	// ȹ�� ��差
// 	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
// 	class UTextBlock* TextBlock_GetGold;
// 
// 	UFUNCTION()
// 	void GetGoldPlayer();
// 
// 
// 
// 	// ȹ�� ����ġ
// 	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
// 	class UTextBlock* TextBlock_getEXP;
// 
// 	UFUNCTION();
// 	void GetEXPPlayer();

};
