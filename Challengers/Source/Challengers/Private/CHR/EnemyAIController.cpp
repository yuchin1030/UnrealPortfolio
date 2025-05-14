// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/EnemyAIController.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BaseWeapon.h"
#include "CHR/BaseGear.h"
#include "DetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	enemyREF = Cast<ABaseEnemy>(GetPawn());
	if (enemyREF)
	{
		nextSearchTime = enemyREF->AIData.targetChangeRate;
		
		if (enemyREF->weapon1)
		{
			nextWeaponTime = enemyREF->weapon1->weaponStat.attackCooldown;
		}

		if (enemyREF->gear)
		{
			nextGearTime = enemyREF->gear->gearStat.useCooldown;
		}

		nextMoveTime = enemyREF->AIData.moveRate;
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (enemyREF != nullptr)
	{
		if (enemyREF->AIState == EAttackState::DIED)
		{
			return;
		}

		if (enemyREF->AIState == EAttackState::READY && enemyREF->bWillChangeWeapon)
		{
			enemyREF->AIState = EAttackState::WEAPONCHANGE;
			return;
		}

		//지정시간마다 가장 가까운 플레이어 캐릭터를 찾는다.
		targetSearchTimer = FMath::Min(targetSearchTimer + DeltaTime, nextSearchTime);
		if (targetSearchTimer == nextSearchTime)
		{
			//UE_LOG(LogTemp, Warning, TEXT("EnemyAI data : %f, %f"), enemyREF->targetDist, enemyREF->AIData.playerFindDist);
			enemyREF->FindPlayer();
			targetSearchTimer = 0.0f;
			nextSearchTime = enemyREF->AIData.targetChangeRate * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
			if (enemyREF->playerREF == nullptr) {
				nextSearchTime = 1.0f;
			}
		}

		gearTimer = FMath::Min(gearTimer + GetWorld()->GetDeltaSeconds(), nextGearTime);
		//공격중이 아니면 공격 타이머 증가
		if (enemyREF->AIState != EAttackState::ATTACK)
		{
			weaponTimer = FMath::Min(weaponTimer + GetWorld()->GetDeltaSeconds(), nextWeaponTime);
		}
		//이동중이 아니면 이동 타이머 증가
		if (enemyREF->GetVelocity().Length() == 0) {
			moveTimer = FMath::Min(moveTimer + DeltaTime, nextMoveTime);
		}

		if (enemyREF->AIState == EAttackState::IDLE && enemyREF->targetDist < enemyREF->AIData.playerFindDist) {
			enemyREF->AIState = EAttackState::READY;
		}

		if (enemyREF->AIState == EAttackState::READY) {
			//UE_LOG(LogTemp, Warning, TEXT("AI ATK Check"));
			switch (enemyREF->enemyPhase)
			{
			case EPhaseState::PHASE1:
			case EPhaseState::PHASE2:
				CheckWeaponTimer();
				break;
			case EPhaseState::PHASE3:
				CheckGearTimer();
				if (enemyREF->AIState == EAttackState::READY) {
					CheckWeaponTimer();
				}
				break;
			default:
				break;
			}
		}

		if (enemyREF->AIState == EAttackState::READY && moveTimer == nextMoveTime) {
			CheckDist();
			nextMoveTime = enemyREF->AIData.moveRate * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
			moveTimer = 0.0f;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("EnemyAI : No enemyREF!!!"));
		enemyREF = Cast<ABaseEnemy>(GetPawn());
	}
}

void AEnemyAIController::CheckGearTimer()
{
	if (enemyREF->gear != nullptr)
	{
		if (gearTimer == nextGearTime) {
			enemyREF->AIState = EAttackState::USINGGEAR;
			nextGearTime = enemyREF->gear->gearStat.useCooldown * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
			gearTimer = 0.0f;
		}
	}
}

void AEnemyAIController::CheckWeaponTimer()
{
	//UE_LOG(LogTemp, Warning, TEXT("AI ATK Time : %f"), weaponTimer);
	switch (enemyREF->enemyPhase)
	{
	case EPhaseState::PHASE1:
		if (enemyREF->weapon1 != nullptr)
		{
			if (weaponTimer == nextWeaponTime) {
				if (enemyREF->targetDist <= enemyREF->weapon1->weaponStat.attackRange) {
					if (HasAuthority())
					{
						UE_LOG(LogTemp, Warning, TEXT("Server Set State Attack"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("Client Set State Attack"));
					}
					enemyREF->ChangeATKState();
					weaponTimer = 0.0f;
					nextWeaponTime = enemyREF->weapon1->weaponStat.attackCooldown * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
				}
				else {
					//UE_LOG(LogTemp, Warning, TEXT("TO"));
					enemyREF->AIState = EAttackState::MOVETOATK;
				}
			}
		}
		break;
	case EPhaseState::PHASE2:
	case EPhaseState::PHASE3:
		if (enemyREF->weapon2 != nullptr)
		{
			if (weaponTimer == nextWeaponTime) {
				if (enemyREF->targetDist <= enemyREF->weapon2->weaponStat.attackRange) {
					enemyREF->ChangeATKState();
					weaponTimer = 0.0f;
					nextWeaponTime = enemyREF->weapon2->weaponStat.attackCooldown * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
				}
				else {
					enemyREF->AIState = EAttackState::MOVETOATK;
				}
			}
		}
		else if (enemyREF->weapon1 != nullptr)
		{
			if (weaponTimer == nextWeaponTime) {
				if (enemyREF->targetDist <= enemyREF->weapon1->weaponStat.attackRange) {
					if (HasAuthority())
					{
						UE_LOG(LogTemp, Warning, TEXT("Server Set State Attack"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("Client Set State Attack"));
					}
					enemyREF->ChangeATKState();
					weaponTimer = 0.0f;
					nextWeaponTime = enemyREF->weapon1->weaponStat.attackCooldown * (1.0f + FMath::RandRange(-enemyREF->AIData.randomArea, enemyREF->AIData.randomArea));
				}
				else {
					//UE_LOG(LogTemp, Warning, TEXT("TO"));
					enemyREF->AIState = EAttackState::MOVETOATK;
				}
			}
		}
		{
		}
		break;
	default:
		break;
	}
}

void AEnemyAIController::CheckDist()
{
	if (enemyREF->targetDist < enemyREF->AIData.battleDist) {
		enemyREF->AIState = EAttackState::MOVRTORUN;
	}
	else{
		enemyREF->AIState = EAttackState::MOVE;
	}
}