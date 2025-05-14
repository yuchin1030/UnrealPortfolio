// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMActor.generated.h"

UCLASS()
class CHALLENGERS_API ABGMActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMActor();

	UPROPERTY(EditAnywhere)
	class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere)
	class UAudioComponent* audioComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	class AOurGameModeBase* OGM = nullptr;
	class ACustomModeBase* CGM = nullptr;
	class ADungeonEditGameModeBase* DGM = nullptr;
	class UOurGameInstance* GI = nullptr;
	class AOurGameStateBase* OGS = nullptr;

	bool bIsPlayStart = false;

	UFUNCTION(BlueprintCallable)
	void PlayBGM();

	UFUNCTION(Server, Reliable)
	void ServerRPC_PlayBGM();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_PlayBGM();

	UFUNCTION()
	void StopBGM();
};
