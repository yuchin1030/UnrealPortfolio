// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonEditGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ADungeonEditGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonEditGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY()
	int32 totalEnemyCost;

	UPROPERTY()
	int32 curEnemyCost;
};
