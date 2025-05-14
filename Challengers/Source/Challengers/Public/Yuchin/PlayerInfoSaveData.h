// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerInfoSaveData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfoSaveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString playerName;

	UPROPERTY(BlueprintReadWrite)
	int32 playerLevel;

	UPROPERTY(BlueprintReadWrite)
	int32 playerGold;

	UPROPERTY(BlueprintReadWrite)
	int32 playerCurrentExp;

	UPROPERTY(BlueprintReadWrite)
	int32 playerMaxExp;

	UPROPERTY(BlueprintReadWrite)
	int32 playerEnemyCost;

	// 무기 레벨 및 공격력
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> weaponLevel;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> currentWeaponStat;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> nextWeaponStat;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> upgWeaponNeedGold;

};

UCLASS()
class CHALLENGERS_API UPlayerInfoSaveData : public USaveGame
{
	GENERATED_BODY()
public:
	UPlayerInfoSaveData();

	UPROPERTY(VisibleAnywhere)
	FPlayerInfoSaveDataStruct playerInfoDataList;
};
