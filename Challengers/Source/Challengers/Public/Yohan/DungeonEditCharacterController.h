// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonEditCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ADungeonEditCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
		
	UPROPERTY()
	class ADungeonEditCharacter* dc;
};
