// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleNPCWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UBattleNPCWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;


	class AMainPlayerController* pc;
	class AChallengersCharacter* Player;
	class ABattleNPC* battleNPC;

	bool bClosed;

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_BattleWidget;
	
	// �޹�� �̹��� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_BackGround;

	// â �ݱ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();



	// ���ΰ�ħ ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Reset;

	UFUNCTION()
	void OnClickReset();



	// �� ���� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_CreateRoom;

	UFUNCTION()
	void OnClickCreateRoom();


};
