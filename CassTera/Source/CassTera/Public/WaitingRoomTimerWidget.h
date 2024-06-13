// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitingRoomTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CASSTERA_API UWaitingRoomTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	// Ÿ�̸� ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Text_Seconds;

	// ���� ���Ӹ��
	UPROPERTY()
	class AWatinGameMode* gm;

	UPROPERTY()
	class AWaitingRoomGameState* gs;

	UFUNCTION()
	void TimerSet();
};
