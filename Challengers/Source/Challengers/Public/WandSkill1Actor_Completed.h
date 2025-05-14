// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill1Actor_Completed.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill1Actor_Completed : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandSkill1Actor_Completed();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	float damagePercent = 5;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	UFUNCTION()
	void WandSkill1();

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill1(FVector hitLoc);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill1(FVector _hitLoc);
};
