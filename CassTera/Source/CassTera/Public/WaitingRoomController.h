// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WaitingRoomController.generated.h"

/**
 * 
 */
UCLASS()
class CASSTERA_API AWaitingRoomController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class AWaitingRoomGameState* gs;
};
