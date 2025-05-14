// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CHR/BaseEnemy.h"
#include "EnemySaveData.generated.h"

USTRUCT(BlueprintType)
struct FEnemySaveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString name = "";
	UPROPERTY(BlueprintReadWrite)
	bool bIsBossType = false;
	UPROPERTY(BlueprintReadWrite)
	int32 totalCost = 0;
	UPROPERTY(BlueprintReadWrite)
	FName bodyRowName = "";
	UPROPERTY(BlueprintReadWrite)
	FName weapon1RowName = "";
	UPROPERTY(BlueprintReadWrite)
	FName weapon2RowName = "";
	UPROPERTY(BlueprintReadWrite)
	FName gearRowName = "";
	UPROPERTY(BlueprintReadWrite)
	struct FAIStat AIData;
};

UCLASS()
class CHALLENGERS_API UEnemySaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UEnemySaveData();

	UPROPERTY(VisibleAnywhere)
	TArray<FEnemySaveDataStruct> enemyDataList;
};