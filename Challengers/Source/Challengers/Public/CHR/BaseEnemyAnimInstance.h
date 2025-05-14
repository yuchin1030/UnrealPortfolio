// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CHR/EnemyAIController.h"
#include "BaseEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UBaseEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float currentVelocity;

	UPROPERTY(BlueprintReadOnly)
	float X;
	
	UPROPERTY(BlueprintReadOnly)
	float Y;

	UPROPERTY(BlueprintReadOnly, Replicated)
	EAttackState enemyState = EAttackState::IDLE;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 attackNum = -1;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 deathNum = -1;

	void SelectAttack(int32 atkAnim);

protected:
	class ABaseEnemy* enemyREF = nullptr;

	UFUNCTION()
	void AnimNotify_Enemy_AttackEnd();

	UFUNCTION()
	void AnimNotify_Enemy_detach_Weapon();

	UFUNCTION()
	void AnimNotify_Enemy_attach_Weapon();

	UFUNCTION()
	void AnimNotify_Enemy_Gear_Anim_SpeedUp();

	UFUNCTION()
	void AnimNotify_Enemy_Gear_Activate();
};
