// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CHR/WeaponStruct.h"
#include "CHR/EnemyBodyStruct.h"
#include "CHR/GearStruct.h"
#include "GJY/MaterialStruct.h"
#include "Weapon1Object.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UWeapon1Object : public UObject
{
	GENERATED_BODY()

public:


	UPROPERTY()
	FweaponSpec WeaponObject1; 

	UPROPERTY()
	FbodySpec BodyObject;
	
	UPROPERTY()
	FName _RowName;

	UPROPERTY()
	FgearSpec AbilityObject;

	UPROPERTY()
	int32 indexNum;

	UPROPERTY()
	bool bIsEquiped;
};
