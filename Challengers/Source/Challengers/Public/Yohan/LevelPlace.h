// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPlace.generated.h"

UCLASS()
class CHALLENGERS_API ALevelPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ALevelPlace();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class USceneComponent* rootComp;

	UPROPERTY()
	class UBoxComponent* setLevelArea;
};
