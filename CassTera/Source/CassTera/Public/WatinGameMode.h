// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WatinGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CASSTERA_API AWatinGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWatinGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// ���� Ÿ�̸�
	float StartTimer = 30.0f;

	// Ÿ�̸� ui
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWaitingRoomTimerWidget> WaitingTimerUI_BP;

	UPROPERTY()
	class UWaitingRoomTimerWidget* WaitingTimerUI;

};
