// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveToDungeonNPC.generated.h"

UCLASS()
class CHALLENGERS_API AMoveToDungeonNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveToDungeonNPC();

protected:
	virtual void BeginPlay() override;
		

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* nPC;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* nPCArea;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMoveToDungeonWidget> moveToDungeonUI_BP;

	UPROPERTY()
	class UMoveToDungeonWidget* moveToDungeonUI;

	class AChallengersCharacter* Player;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
