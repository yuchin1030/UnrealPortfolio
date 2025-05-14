// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHR/BaseGear.h"
#include "ShootGear.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API AShootGear : public ABaseGear
{
	GENERATED_BODY()
	
public:
	void DataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy) override;

	void ActivateGear() override;

	UPROPERTY(EditDefaultsOnly)
	float damage = 100.0f;

	TArray<class ABaseBullet*> bulletArray;


	UFUNCTION(Server, Reliable)
	void ServerRPC_ShootBullet();
};
