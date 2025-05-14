// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawRangeActor.generated.h"

UCLASS()
class CHALLENGERS_API ADrawRangeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawRangeActor();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class UDecalComponent* outCircle;

	UPROPERTY(EditDefaultsOnly)
	class UDecalComponent* inCircle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ABaseEnemy* enemyREF;

	float inSize;

	float outSize;

	void Init(class ABaseEnemy* newEnemy);
};
