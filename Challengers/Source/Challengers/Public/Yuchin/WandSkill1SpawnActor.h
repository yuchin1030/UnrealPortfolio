// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill1SpawnActor.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill1SpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandSkill1SpawnActor();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraSystem* fx;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MySettings)
    class UNiagaraComponent* fxComp;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	// 스킬계수 (스킬포인트 계수)
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	bool bHitWandSkill1;

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill1Hit();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill1Hit(FVector _enemyLoc);


};
