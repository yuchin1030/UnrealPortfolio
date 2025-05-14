// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EAttackState : uint8 {
	IDLE,
	READY,
	MOVE,
	MOVRTORUN,
	MOVETOATK,
	ATTACK,
	USINGGEAR,
	WEAPONCHANGE,
	DIED,
};

UCLASS()
class CHALLENGERS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	EAttackState enemyState = EAttackState::IDLE;

	class ABaseEnemy* enemyREF;

	float targetSearchTimer = 0.0f;
	float nextSearchTime;

	float weaponTimer = 0.0f;
	float nextWeaponTime;

	float gearTimer = 0.0f;
	float nextGearTime;

	float moveTimer = 0.0f;
	float nextMoveTime;

	void CheckGearTimer();

	void CheckWeaponTimer();

	void CheckDist();
};
