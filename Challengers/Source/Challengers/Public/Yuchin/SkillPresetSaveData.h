// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SkillPresetSaveData.generated.h"

USTRUCT(BlueprintType)
struct FSkillPresetSaveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString playerName;

	UPROPERTY(BlueprintReadWrite)
	int32 canUseSkillPoint;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> skillPointArr;
};

UCLASS()
class CHALLENGERS_API USkillPresetSaveData : public USaveGame
{
	GENERATED_BODY()
public:
	USkillPresetSaveData();

	UPROPERTY(VisibleAnywhere)
	FSkillPresetSaveDataStruct skillDataList;
};
