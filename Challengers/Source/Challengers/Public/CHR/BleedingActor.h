// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BleedingActor.generated.h"

UCLASS()
class CHALLENGERS_API ABleedingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABleedingActor();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* niagara;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(ReplicatedUsing = Onrep_Bleed)
	FVector activePos;

	UPROPERTY(Replicated)
	FRotator activeRot;

	void ActiveBleed(FVector _activePos, FVector _atkPos);

	UFUNCTION(Server, Reliable)
	void ServerRPC_ActiveBleed(FVector _activePos, FVector _atkPos);

	UFUNCTION()
	void Onrep_Bleed();
};
