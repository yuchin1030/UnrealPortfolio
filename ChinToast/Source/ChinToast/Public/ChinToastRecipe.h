// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
#include "ChinToastRecipe.generated.h"

USTRUCT(BlueprintType)
struct FFoodData:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_material1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_material2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_material3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_material4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString D_material5;
};

UCLASS()
class CHINTOAST_API AChinToastRecipe : public AActor
{
	GENERATED_BODY()
	
public:	
	AChinToastRecipe();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	TMap<FString, UStaticMesh*> ingredients; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TMap<FString, UTexture2D*> foodimage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<FString> makedRecipe;

	TArray<FString> recipe1;
	TArray<FString> recipe2;
	TArray<FString> recipe3;
	TArray<FString> recipe4;
	TArray<FString> recipe5;
	TArray<FString> recipe6;

	UStaticMesh* GetRecipe(FString metarialname);

	UFUNCTION(BlueprintCallable)
	void SetRandomMenu();

	
};
