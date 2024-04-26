// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraShakeBase.h>
#include "CppTurret.generated.h"

UCLASS()
class MARIOREALRECENT_API ACppTurret : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrow;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrowV1;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrowV2;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrowV3;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrowV4;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrowW;

	UPROPERTY(EditAnywhere)
	float delayTime = 10.0f;

	UPROPERTY(EditAnywhere)
	float BalldelayTime = 1.5f;



	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_ball> enemy_bp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_ball> enemyFire_bp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_Violethat> violet_bp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_WhiteHat> white_bp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_FirstVioletHat> violet_bp1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKoopa_SecondVioletHat> violet_bp2;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Beam1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Target1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Target2;



	UPROPERTY(VisibleAnywhere)
	USceneComponent* FollowTarget;

	UPROPERTY()
	FTimerHandle ChangeTargetTimerhandle;

	UPROPERTY()
	FTimerHandle TraceTimerhandle;

	//rotation related variables
	int32 TimerCount = 0;
	FRotator LookAtRotation;
	FRotator TargetRotation;
	FRotator RotationDelta;

	UPROPERTY(EditAnywhere)
	float anytimeScaler = 1.0f;

	UPROPERTY(EditAnywhere)
	float ChangeTargetDelay=3.5f;

	UPROPERTY(EditAnywhere)
	int32 ChangeNumber=0;


	UPROPERTY(EditAnywhere)
	float RotationRateMultiplier=1.f;

	UPROPERTY()
	AActor* Enemy;

	UFUNCTION()
	void UpdateLookAtTarget(float DeltaTime);

	UFUNCTION()
	void ChangeBeamTarget();

	UFUNCTION()
	void TraceBeam();

	UFUNCTION()
	void CheckEnemy(AActor* HitActor);

	UFUNCTION()
	void FollowEnemy(float DeltaTime);

	UFUNCTION()
	void Shoot();

	
public:	
	// Sets default values for this actor's properties
	ACppTurret();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class UAnimationAsset*> Anims;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 KoopaHealth=47;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float anyTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TimeLineTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSpin = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector moveDirection;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFireBall = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsWearingHat = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	

};
