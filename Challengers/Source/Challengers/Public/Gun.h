// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class CHALLENGERS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();



protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

    UPROPERTY(VisibleAnywhere, Category = MySettings)
    class UNiagaraComponent* fxComp;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	UPROPERTY()
	TArray<AActor*> enemies;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	UPROPERTY()
	class AChallengersCharacter* cc;

	UPROPERTY()
	FVector startLoc;

	bool bHitGunBasic;

	UFUNCTION()
	void GunBasicAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
	class UNiagaraComponent* WeaponEffect;

	UFUNCTION(Server, Reliable)
	void ServerRPC_GunBasicAttack(AActor* _OtherActor);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_GunBasicAttack(FVector hitLoc);

};
