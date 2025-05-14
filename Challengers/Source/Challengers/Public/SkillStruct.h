// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillStruct.generated.h"

UCLASS()
class CHALLENGERS_API ASkillStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillStruct();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(BlueprintType)
struct FSkillsInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DamagePower;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefendPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UsedMP;
};
