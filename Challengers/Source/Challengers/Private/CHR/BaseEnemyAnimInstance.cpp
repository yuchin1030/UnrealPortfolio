// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseEnemyAnimInstance.h"
#include "CHR/BaseEnemy.h"
#include "Net/UnrealNetwork.h"

void UBaseEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	enemyREF = Cast<ABaseEnemy>(TryGetPawnOwner());
}

void UBaseEnemyAnimInstance::NativeBeginPlay()
{
	if (enemyREF) {
		enemyState = enemyREF->AIState;
	}
}

void UBaseEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (enemyREF) {
		currentVelocity = enemyREF->GetVelocity().Length();
		X = enemyREF->forwardSpeed;
		Y = enemyREF->rightSpeed;
		enemyState = enemyREF->AIState;
		attackNum = enemyREF->atkAnimSelect;
		deathNum = enemyREF->deathAnimSelect;
	}
}

void UBaseEnemyAnimInstance::SelectAttack(int32 atkAnim)
{
	attackNum = atkAnim;
	if (enemyState == EAttackState::ATTACK) {
		UE_LOG(LogTemp, Warning, TEXT("Anim ATTACK"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Anim NOT ATTACK"));
	}
	UE_LOG(LogTemp, Warning, TEXT("attackNum : %d"), attackNum);
}

void UBaseEnemyAnimInstance::AnimNotify_Enemy_AttackEnd()
{
	if (enemyREF) {
		//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_Enemy_AttackEnd()"));
		attackNum = -1;
		enemyREF->Anim_AttackEnd();
	}
}

void UBaseEnemyAnimInstance::AnimNotify_Enemy_detach_Weapon()
{
	if (enemyREF) {
		enemyREF->Anim_detach_Weapon();
	}
}

void UBaseEnemyAnimInstance::AnimNotify_Enemy_attach_Weapon()
{
	if (enemyREF) {
		enemyREF->Anim_attach_Weapon();
	}
}

void UBaseEnemyAnimInstance::AnimNotify_Enemy_Gear_Anim_SpeedUp()
{
	Montage_SetPlayRate(GetCurrentActiveMontage(), 1.0f);
}

void UBaseEnemyAnimInstance::AnimNotify_Enemy_Gear_Activate()
{
	if (enemyREF) {
		enemyREF->Anim_ActiveGear();
	}
}

void UBaseEnemyAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 에너미 체력 동기화
	DOREPLIFETIME(UBaseEnemyAnimInstance, attackNum);
	DOREPLIFETIME(UBaseEnemyAnimInstance, deathNum);
	DOREPLIFETIME(UBaseEnemyAnimInstance, enemyState);
}