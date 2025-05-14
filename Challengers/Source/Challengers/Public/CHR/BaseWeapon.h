// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponStruct.h"
#include "BaseWeapon.generated.h"

UCLASS()
class CHALLENGERS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* attackCollision;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* weaponBody;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY()
	class ABaseEnemy* enemyREF;

	FName rowName;

	struct FweaponSpec weaponStat;

	int32 atkMoveNum;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> damageType;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* swingSound;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* hitSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABleedingActor> bleed_bp;

	UPROPERTY(EditDefaultsOnly)
	class ABleedingActor* bleed;

	virtual void dataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy);

	UFUNCTION(Server, Reliable)
	void ServerRPC_dataInit(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy);

	void ActiveDmgBox();

	void DeactiveDmgBox();

	void MakeBleed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_MakeBleed();

	void ClearBleed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ClearBleed();

	UFUNCTION()
	void WeaponHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
