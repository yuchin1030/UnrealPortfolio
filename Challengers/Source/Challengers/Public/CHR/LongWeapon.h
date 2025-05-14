// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHR/BaseWeapon.h"
#include "LongWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ALongWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	void dataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy) override;

	UFUNCTION(Server, Reliable)
	void ServerRPC_LongDataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseBullet> shotBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseAreaAtk> auraBP;

	UPROPERTY(EditDefaultsOnly)
	int32 magicSelectNum = 1;

	bool bIsAreaBefore = false;

	UPROPERTY(EditDefaultsOnly)
	int32 bulletFireNum = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 auraFireNum = 1;

	TArray<class ABaseBullet*> bulletArray;

	TArray<class ABaseAreaAtk*> auraArray;

	UPROPERTY(Replicated)
	FVector newFirePos;

	void FireMagic(FVector fireLoc, FRotator fireRot, FVector targetLoc);

	UFUNCTION(Server, Reliable)
	void ServerRPC_FireMagic(FVector fireLoc, FRotator fireRot, FVector targetLoc);

	void ClearBullet();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ClearBullet();

};
