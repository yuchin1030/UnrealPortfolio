// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandBasic.generated.h"

UCLASS()
class CHALLENGERS_API AWandBasic : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandBasic();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UNiagaraComponent* fx;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	float speed = 2500;

	bool bHitWandBasic;

	UPROPERTY()
	TArray<AActor*> enemies;

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandBasicAttack(AActor* _OtherActor);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandBasicAttack(FVector hitLoc);

	UFUNCTION()
	void WandBasicActivate(bool bActivate);

	UFUNCTION()
	void WandBasicAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
