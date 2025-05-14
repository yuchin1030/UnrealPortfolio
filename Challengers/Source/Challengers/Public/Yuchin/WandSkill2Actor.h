// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill2Actor.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill2Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWandSkill2Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	UFUNCTION()
	void WandSkill2();

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill2();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill2(FVector _enemyLoc);
};
