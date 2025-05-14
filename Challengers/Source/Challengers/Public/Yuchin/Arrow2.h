// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow2.generated.h"

UCLASS()
class CHALLENGERS_API AArrow2 : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrow2();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditDefaultsOnly, Category=MySettings)
	//class UChildActorComponent* VFXActor;


};
