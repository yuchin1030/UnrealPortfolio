// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPreset.generated.h"

UCLASS()
class CHALLENGERS_API ATestPreset : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestPreset();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

USTRUCT()
struct FPresetSample : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillPoint;
	
};
