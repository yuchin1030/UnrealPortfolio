// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bow.generated.h"

UCLASS()
class CHALLENGERS_API ABow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABow();


public:	


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UStaticMeshComponent* Bow;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UNiagaraComponent* Effect;


	UFUNCTION()
	void UpgradeBowEffect(int32 weaponLevel);

	FVector BowEffectScale = FVector(0,0,0);

};
