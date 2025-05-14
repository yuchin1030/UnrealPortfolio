// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wand.generated.h"

UCLASS()
class CHALLENGERS_API AWand : public AActor
{
	GENERATED_BODY()
	
public:	
	AWand();



protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditAnywhere, Category = "MySettings", Replicated)
	class UNiagaraSystem* basicHitVFX;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UStaticMeshComponent* wandMeshComp;

	

	UPROPERTY()
	class AWandSkill2Actor* skill2Actor;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	TSubclassOf<class AWandSkill2Actor> skill2Actor_bp;

	UPROPERTY()
	FTimerHandle spawnHdl;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	float delayTime = 0.05f;

	UPROPERTY()
	FVector _curForward;

	UPROPERTY()
	FVector _curLoc;

	float currentTime = 0;
	float stopTime = 0;

	bool bWandSkill1;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USoundBase* wandBasicHitSound;

	/*UFUNCTION()
	void WandBasicAttack(FVector _basicLoc);*/

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandBasicAttack(FVector _basicLoc, AChallengersCharacter* player);

	UFUNCTION()
	void WandSkill1(FVector curForward, FVector curLoc);

	//UFUNCTION(Server, Reliable)
	//void ServerRPC_WandSkill1(FVector curForward, FVector curLoc, AChallengersCharacter* player);

	//UFUNCTION(NetMulticast, Reliable)
	//void MultiRPC_WandSkill1(FVector curForward_, FVector curLoc_);

	UFUNCTION()
	void WandSkill2();
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill2(FVector curLoc, AChallengersCharacter* player);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill2(FVector curLoc_);


	UFUNCTION()
	void WandSkill3();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly ,Category = "Niagara")
	class UNiagaraComponent* WeaponEffect;

	UFUNCTION()
	void UpgradeWandEffect(int32 weaponLevel);

	class AChallengersCharacter* CC;

	FVector EffectWandScale = FVector (0,0,0);
};
