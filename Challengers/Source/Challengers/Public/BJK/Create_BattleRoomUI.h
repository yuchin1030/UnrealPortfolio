// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Create_BattleRoomUI.generated.h"




UCLASS()
class CHALLENGERS_API UCreate_BattleRoomUI : public UUserWidget
{
	GENERATED_BODY()
	
// protected:
// 
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Join;

	// 방 입장하기
	UFUNCTION()
	void OnClickJoinRoom();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_RoomName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerNum;


};

