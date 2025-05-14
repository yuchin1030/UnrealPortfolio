// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialStruct.h"
#include "ColorStruct.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UColorStruct : public UObject
{
	GENERATED_BODY() 

public:


	UPROPERTY()
	class UPlayerCustomizer* PC;

	UPROPERTY()
	FMaterialType MaterialObject;
	
	UPROPERTY()
	FMaterialType MaterialObject2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* btnColor;

	UPROPERTY()
	int RowNumber;

};
