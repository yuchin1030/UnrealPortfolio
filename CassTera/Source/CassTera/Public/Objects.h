// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects.generated.h"

UCLASS()
class CASSTERA_API AObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	UStaticMeshComponent* objectComp;

	// �������� ���� �̱�
	int32 rate = 40;

	// �������� ������Ʈ ����
	UFUNCTION()
	void RandomSpawn();
};
