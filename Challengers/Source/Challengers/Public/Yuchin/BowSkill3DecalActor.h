// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "BowSkill3DecalActor.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ABowSkill3DecalActor : public ADecalActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void DestroyDecal();
};
