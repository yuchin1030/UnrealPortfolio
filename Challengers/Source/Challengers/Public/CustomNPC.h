// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "CustomNPC.generated.h"

UCLASS()
class CHALLENGERS_API ACustomNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACustomNPC();

	AChallengersCharacter* Player;

	UPROPERTY(EditAnywhere,Category = NPC)
	class UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere,Category = NPC)
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
