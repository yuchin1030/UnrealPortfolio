// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHR/BaseEnemyAnimInstance.h"
#include "CHR/EnemyAIController.h"
#include "CEnemyAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UCEnemyAnimInst : public UBaseEnemyAnimInstance
{
	GENERATED_BODY()
	
public:

private:

	UFUNCTION()
	void AnimNotify_Enemy_ActiveBox();

	UFUNCTION()
	void AnimNotify_Enemy_DeactiveBox();
};
