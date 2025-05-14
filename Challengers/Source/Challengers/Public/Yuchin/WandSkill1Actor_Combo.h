// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill1Actor_Combo.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill1Actor_Combo : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandSkill1Actor_Combo();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	float damagePercent = 2;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	UFUNCTION()
	void WandSkill1_Combo();

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill1_Combo();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill1_Combo(FVector hitLoc);
};
