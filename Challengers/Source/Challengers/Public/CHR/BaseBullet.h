// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class CHALLENGERS_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* hitColl;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* niagara;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSetting")
	class UNiagaraSystem* hitFX;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSetting")
	class USoundBase* fireSound;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSetting")
	class USoundBase* hitSound;

	UPROPERTY()
	class ABaseEnemy* enemyREF;

	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	bool bTIsSlow_FISHold = true;

	//탄환속도
	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float speed = 2000;

	//발사전 속도가 증가하는 시간(Lerp)
	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float correctDuration = 0.5f;

	float speedCorrect = 0.0f;

	//발사전 속도가 증가하는 시간(easeIn)
	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float holdDuration = 2;

	UPROPERTY(Replicated)
	float correctTime = 0.0f;

	//총알의 지속시간
	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float duration = 2.0f;

	float durationTime = 0.0f;

	float disappearTime = 0.3f;

	UPROPERTY(ReplicatedUsing = OnRep_Disappear)
	float alpha = 1.0f;

	bool startFly = true;

	UPROPERTY(ReplicatedUsing = OnRep_MoveBullet)
	FVector bulletLoc;

	UPROPERTY(EditAnywhere, Category = "BulletSetting")
	float damage = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_Appear)
	bool bIsActive = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> damageType;

	void DataInit(float _damage, class ABaseEnemy* shooter);

	UFUNCTION(Server, Reliable)
	void ServerRPC_StartSpeedCorrect();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BulletFly();

	UFUNCTION(Server, Reliable)
	void ServerRPC_EndBulletFly();

	UFUNCTION()
	void OnRep_MoveBullet();

	UFUNCTION()
	void OnRep_Disappear();

	UFUNCTION()
	void BulletHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
	void ServerRPC_HitEffect();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_HitEffect();

	void BulletActivate(FVector fireLoc, FRotator fireRot);

	UFUNCTION(Server, Reliable)
	void ServerRPC_Activate(FVector fireLoc, FRotator fireRot);

	UFUNCTION()
	void OnRep_Appear();

	void BulletDeactivate();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Deactivate();
};
