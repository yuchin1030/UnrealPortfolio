// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowSkill3Actor.generated.h"

UCLASS()
class CHALLENGERS_API ABowSkill3Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABowSkill3Actor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	UFUNCTION()
	void BowSkill3();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ApplyDamage(FVector hitLoc);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ApplyDamage(FVector _hitLoc);
};
