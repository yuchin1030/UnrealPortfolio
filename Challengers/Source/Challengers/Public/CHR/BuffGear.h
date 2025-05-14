// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHR/BaseGear.h"
#include "BuffGear.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ABuffGear : public ABaseGear
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 buffNum = 0;

	UPROPERTY(EditDefaultsOnly)
	float buffPower = 1.5f;

	void ActivateGear() override;
};
