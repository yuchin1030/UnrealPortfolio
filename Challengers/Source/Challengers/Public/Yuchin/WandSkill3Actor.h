// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill3Actor.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill3Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandSkill3Actor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USceneComponent* sceneComp;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx2;
	
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx3;
	
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx4;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx5;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY()
	bool bDamaging;

	bool bIsAbleAtk = true;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	UFUNCTION()
	void WandSkill3Activate(bool bActivate);

	UFUNCTION()
	void WandSkill3(FVector start, FVector end, class AChallengersCharacter* playerChar);

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill3(FVector start_, FVector end_, class AChallengersCharacter* playerChar_);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill3(FVector hitLoc);
};
