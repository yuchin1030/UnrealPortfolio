// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/DrawRangeActor.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BaseWeapon.h"
#include "Components/DecalComponent.h"

// Sets default values
ADrawRangeActor::ADrawRangeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	outCircle = CreateDefaultSubobject<UDecalComponent>(TEXT("OutLine"));
	outCircle->SetupAttachment(rootComp);
	outCircle->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	outCircle->DecalSize = FVector(10.0f, 0.0f, 0.0f);

	inCircle = CreateDefaultSubobject<UDecalComponent>(TEXT("InCircle"));
	inCircle->SetupAttachment(rootComp);
	inCircle->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	inCircle->DecalSize = FVector(10.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ADrawRangeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrawRangeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (enemyREF)
	{
		if ((enemyREF->enemyPhase == EPhaseState::PHASE1 && enemyREF->weapon1) || (enemyREF->enemyPhase != EPhaseState::PHASE1 && enemyREF->weapon2 == nullptr && enemyREF->weapon1)) {
			inSize = enemyREF->weapon1->weaponStat.attackRange;
			//UE_LOG(LogTemp, Warning, TEXT("Draw In Size : %f"), inSize);
		}
		else if (enemyREF->weapon2) {
			inSize = enemyREF->weapon2->weaponStat.attackRange;
		}
		inCircle->DecalSize = FVector(10.0f, inSize, inSize);

		FVector newLoc = enemyREF->GetActorLocation();
		newLoc.Z = 1.0f;
		SetActorLocation(newLoc);
		newLoc.Z = 0.0f;
		SetActorLocation(newLoc);
	}
	else{
		SetActorLocation(FVector(0.0f, 0.0f, 4100.0f));
	}
}

void ADrawRangeActor::Init(ABaseEnemy* newEnemy)
{
	enemyREF = newEnemy;
	if (enemyREF) {
		outSize = enemyREF->AIData.playerFindDist;
		outCircle->DecalSize = FVector(10.0f, outSize, outSize);

		SetActorLocation(FVector(0.0f, 0.0f, 4100.0f));
		FVector newLoc = enemyREF->GetActorLocation();
		newLoc.Z = 0;
		SetActorLocation(newLoc);
		//UE_LOG(LogTemp, Warning, TEXT("Draw Out Size : %f"), outSize);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Init No Enemy!"));
	}
}

