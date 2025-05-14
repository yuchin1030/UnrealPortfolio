// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowSkill2Actor.generated.h"

UCLASS()
class CHALLENGERS_API ABowSkill2Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABowSkill2Actor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USceneComponent* defaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float speed = 6000;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float speedCorrect = 1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	/*UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damageGage = 0;*/

	UPROPERTY(BlueprintReadWrite)
	float damageValue = 0;

	float damage = 0;

	UPROPERTY(ReplicatedUsing = OnRep_ChangeScale)
	FVector scale;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	UPROPERTY()
	class AChallengersCharacter* cc;

	UPROPERTY()
	FVector startLoc;

	UFUNCTION()
	void SetDamageGage(float damageGage);

	UFUNCTION(Server, Reliable)
	void ServerRPC_SetDamageGage(float _damageGage);

	UFUNCTION()
	void OnRep_ChangeScale();

	UFUNCTION()
	void OnFxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
	void ServerRPC_ApplyDamage(FVector hitLoc);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ApplyDamage(FVector _hitLoc);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
