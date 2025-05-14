// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CHR/BaseEnemy.h"
#include "SaveDungeonData.generated.h"

/**
 * 
 */
 USTRUCT(BlueprintType)
struct FObjectSaveData
{
    GENERATED_BODY()

    UPROPERTY()
    FName bodyRow;

    UPROPERTY()
    FName weaponRow1;

    UPROPERTY()
    FName weaponRow2;

    UPROPERTY()
    FName gearRow;

    UPROPERTY()
    FAIStat aiDT;

    UPROPERTY()
    FVector Location;

    UPROPERTY()
    FRotator Rotation;

    UPROPERTY()
    FString enemyClass;
};

USTRUCT(BlueprintType)
struct FDunInfo
{
    GENERATED_BODY()

    UPROPERTY()
    FString dunName;

    UPROPERTY()
    FString dunType;

    UPROPERTY()
    int32 dunTotalCost = 0;

    UPROPERTY()
    TArray<FObjectSaveData> savedEnemys;
};



UCLASS()
class CHALLENGERS_API USaveDungeonData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
    TArray<FDunInfo> dunInfos;
};
