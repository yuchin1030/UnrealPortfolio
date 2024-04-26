// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "MarioPunchingCap.generated.h"

UCLASS()
class MARIOREALRECENT_API AMarioPunchingCap : public AActor
{
	GENERATED_BODY()
	
public:	
	AMarioPunchingCap();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, Category="MySettings")
	//class UBoxComponent* cupaHatCollision;

	//UPROPERTY(EditAnywhere, Category="MySettings")
	//class USkeletalMeshComponent* cupaHat;

	//UPROPERTY(EditAnywhere, Category="MySettings")
	//class UInterpToMovementComponent* interpMovement;

	//UFUNCTION()
	//void CupaHatRotate();

	////class UCurveFloat;

	//FTimeline CurveTimeline;

	//UPROPERTY(EditAnywhere, Category = "Timeline")
	//class UCurveFloat* CurveFloat;

	//UPROPERTY()
	//FRotator StartRot;

	//UPROPERTY()
	//FRotator EndRot;

	//UPROPERTY(EditAnywhere, Category = "Timeline")
	//float offset;	// 내가 줄 값

	//UFUNCTION()
	//void TimelineProgress(float Value);

};
