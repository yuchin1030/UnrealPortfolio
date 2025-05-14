// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaterialStruct.generated.h"

UCLASS()
class CHALLENGERS_API AMaterialStruct : public AActor
{
	GENERATED_BODY()
	
};

USTRUCT()
struct FMaterialType : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* MaterialInst;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* ColorUI;
};
