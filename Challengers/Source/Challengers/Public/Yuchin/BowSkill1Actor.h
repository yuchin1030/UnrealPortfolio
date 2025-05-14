// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowSkill1Actor.generated.h"

UCLASS()
class CHALLENGERS_API ABowSkill1Actor : public AActor
{
	GENERATED_BODY()
	
public:
	ABowSkill1Actor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USceneComponent* defaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UBoxComponent* boxComp1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx2;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UBoxComponent* boxComp2;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UNiagaraComponent* fx3;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UBoxComponent* boxComp3;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float speed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float speedCorrect = 1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	float damagePercent = 1;

	UPROPERTY()
	int32 weaponAttackPower = 30;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UParticleSystem* hitFX;

	UPROPERTY()
	class AChallengersCharacter* cc;

	UPROPERTY()
	FVector startLoc;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	UFUNCTION()
	void OnFx1BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFx2BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFx3BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ArrowActivate(bool bActivate);

	UPROPERTY(Replicated)
	bool bIsActive;

	UFUNCTION(Server, Reliable)
	void ServerRPC_ArrowActivate(bool bActivate);

	UFUNCTION(Server, Reliable)
	void ServerRPC_ApplyDamage(AActor* _OtherActor);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ApplyDamage(FVector hitLoc);

	FORCEINLINE void PlayerInit(class AChallengersCharacter* _player){
		player = _player;
	};

	class AChallengersCharacter* player;
};
