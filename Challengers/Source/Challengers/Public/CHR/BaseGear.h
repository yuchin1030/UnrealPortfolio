// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GearStruct.h"
#include "BaseGear.generated.h"

UCLASS()
class CHALLENGERS_API ABaseGear : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGear();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* gearEffectComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float activeTime = 0.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY()
	class ABaseEnemy* enemyREF;

	FName rowName;

	int32 gearNum;

	struct FgearSpec gearStat;

	virtual void DataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy);

	virtual void ActivateGear();
};
