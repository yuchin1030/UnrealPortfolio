// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WandSkill2Actor_Combo.generated.h"

UCLASS()
class CHALLENGERS_API AWandSkill2Actor_Combo : public AActor
{
	GENERATED_BODY()
	
public:	
	AWandSkill2Actor_Combo();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class USceneComponent* defaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UNiagaraComponent* fxComp;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box2;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box3;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box4;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box5;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
    class UBoxComponent* box6;

	UPROPERTY(EditAnywhere, Category = MySettings)
    UNiagaraSystem* hitVFX;

	float damagePercent = 2;

	UFUNCTION()
	void WandSkill2ComboHit(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill2ComboHit(FVector hitLoc);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill2ComboHit(FVector _hitLoc);
};
