// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAreaAtk.generated.h"

UCLASS()
class CHALLENGERS_API ABaseAreaAtk : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* hitColl;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* niagara;

	UPROPERTY(EditDefaultsOnly)
	class UAudioComponent* playingLoop;

public:	
	// Sets default values for this actor's properties
	ABaseAreaAtk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ABaseEnemy* enemyREF;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> damageType;

	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float damage = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float atkRadius = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<class AWarningCircleActor> warningCircle_BP;

	class AWarningCircleActor* warningCircle;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FVector size = FVector(1.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float warningTime = 3.0f;

	float warningVolumeTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float activeTime = 3.0f;

	UPROPERTY(Replicated)
	float currentTime = 0.0f;

	bool bIsWarning = true;

	bool bIsEnd = false;

	FTimerHandle destroyTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 atkCount = 3;

	float atkTime;

	float nextAtkTime = 0.0f;

	UFUNCTION()
	void ClearEffect();

	void DataInit(float _damage, class ABaseEnemy* shooter);

	void StartAtk(FVector AtkLoc);

	UFUNCTION(Server, Reliable)
	void ServerRPC_StartAtk(FVector AtkLoc);

	UFUNCTION(Server, Reliable)
	void ServerRPC_SpawnWarning();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ActiveWarning();

	UFUNCTION()
	void WarningEnd();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ActiveEffect();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ActiveEffect();

	UFUNCTION(Server, Reliable)
	void ServerRPC_DeactiveEffect();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_DeactiveEffect();

	void EraseWarning();

	UFUNCTION(Server, Reliable)
	void ServerRPC_EraseWarning();

	UFUNCTION()
	void OnOverlaped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
