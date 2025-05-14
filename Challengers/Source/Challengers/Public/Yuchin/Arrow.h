// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class CHALLENGERS_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrow();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category=MySettings)
	class UChildActorComponent* VFXActor;

	UPROPERTY(EditDefaultsOnly, Category=MySettings)
	class ABowSkill1Actor* bowSkill1Actor;

};
