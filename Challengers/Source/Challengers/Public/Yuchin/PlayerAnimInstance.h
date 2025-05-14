// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly)
	class AChallengersCharacter* playerREF;

	UFUNCTION()
	void AnimNotify_Player_AtkEnd();

	UFUNCTION()
	void AnimNotify_PlusMP();

	UFUNCTION()
	void AnimNotify_CanAttackAgain();

	UFUNCTION()
	void AnimNotify_CanWandBsAttackAgain();

	UFUNCTION()
	void AnimNotify_SpawnWand3();

	UFUNCTION()
	void AnimNotify_SpawnArrowBasic();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_SpawnArrow1();

	UFUNCTION()
	void AnimNotify_CantMove();

	UFUNCTION()
	void AnimNotify_IncreaseSpeed();

	UFUNCTION()
	void AnimNotify_InvisibleDash();
	
	UFUNCTION()
	void AnimNotify_Footstep();

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* footstepSound;
};
