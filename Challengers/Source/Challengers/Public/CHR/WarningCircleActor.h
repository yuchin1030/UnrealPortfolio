// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarningCircleActor.generated.h"

//커스텀 델리게이트 경고시간 끝남
DECLARE_DELEGATE(FWarningEnd);

UCLASS()
class CHALLENGERS_API AWarningCircleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarningCircleActor();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class UDecalComponent* outCircle;

	UPROPERTY(EditDefaultsOnly)
	class UDecalComponent* inCircle;

	UPROPERTY(EditDefaultsOnly)
	class UAudioComponent* playingCasting;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FWarningEnd warningTimeEndDelegate;

	UPROPERTY(ReplicatedUsing = OnRep_SizeChange)
	FVector size = FVector(1.0f, 0.1f, 0.1f);

	FVector targetSize;

	float lifeTime;

	float warningSoundTime;

	UPROPERTY(Replicated)
	float lerpTime = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_ShowCircle)
	bool bIsStart = false;

	void Init(FVector InputSize, float InputLifeTime);

	UFUNCTION(Server, Reliable)
	void ServerRPC_Init(FVector _InputSize, float _InputLifeTime);

	UFUNCTION(Server, Reliable)
	void ServerRPC_SizeChange();

	UFUNCTION()
	void OnRep_SizeChange();

	void WarningActivate(FVector fireLoc);

	UFUNCTION(Server, Reliable)
	void ServerRPC_Activate(FVector fireLoc);

	UFUNCTION()
	void OnRep_ShowCircle();

	void WarningDeactivate();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Deactivate();
};
