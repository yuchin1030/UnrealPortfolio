// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkeletalMeshStructure.generated.h"

UCLASS()
class CHALLENGERS_API ASkeletalMeshStructure : public AActor
{
	GENERATED_BODY()
	

};

USTRUCT()
struct FSkeletalMeshType : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalBody;
	
};

