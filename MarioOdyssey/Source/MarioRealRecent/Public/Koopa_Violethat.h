// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Koopa_Violethat.generated.h"

UCLASS()
class MARIOREALRECENT_API AKoopa_Violethat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKoopa_Violethat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category="MySettings|Components")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category="MySettings|Components")
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	int32 traceRate = 50;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	float moveSpeed = 600;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	float VioDel = 0;
private:
	FVector moveDirection;

	FVector moveDirection1;

	FRotator WhiteRot = FRotator(0, 15, 0);
};
