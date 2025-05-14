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

	// Panel 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_BattleWidget;
	
	// 뒷배경 이미지 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_BackGround;

	// 창 닫기 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();



	// 새로고침 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Reset;

	UFUNCTION()
	void OnClickReset();



	// 방 생성 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_CreateRoom;

	UFUNCTION()
	void OnClickCreateRoom();


};
