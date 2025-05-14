// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class CHALLENGERS_API USkillSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillSystemComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UDataTable* DT_PresetSample;

	UPROPERTY()
	int32 SwordSkillCnt = 3;

	UPROPERTY()
	TArray<bool> SwordSkillArr;

	UPROPERTY()
	int32 WandSkillCnt = 3;

	UPROPERTY()
	TArray<bool> WandSkillArr;

	UPROPERTY()
	int32 GunSkillCnt = 3;

	UPROPERTY()
	TArray<bool> GunSkillArr;

	//UFUNCTION(BlueprintCallable)
	//void LoadPreset();
};
