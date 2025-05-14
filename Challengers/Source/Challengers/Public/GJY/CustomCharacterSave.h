// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomCharacterSave.generated.h"




UCLASS()
class CHALLENGERS_API UCustomCharacterSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UCustomCharacterSave();

	UPROPERTY()
	bool bIsMan;
	UPROPERTY()
	TArray<FName> _FinalMeshArr;

	UPROPERTY()
	FString playerName;

	UPROPERTY()
	int _ClothesColorNum;
	
	UPROPERTY()
	int _HairColorNum;

	UPROPERTY()
	bool bGlove;


};
