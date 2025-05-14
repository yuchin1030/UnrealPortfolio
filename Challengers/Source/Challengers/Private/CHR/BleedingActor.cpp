// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BleedingActor.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABleedingActor::ABleedingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	niagara->SetupAttachment(rootComp);

	Tags.Add(FName("Enemy"));

}

void ABleedingActor::ActiveBleed(FVector _activePos, FVector _atkPos)
{
	ServerRPC_ActiveBleed(_activePos, _atkPos);
}

void ABleedingActor::ServerRPC_ActiveBleed_Implementation(FVector _activePos, FVector _atkPos)
{
	activePos = _activePos;
	activeRot = (_atkPos - activePos).Rotation();
	Onrep_Bleed();
}

void ABleedingActor::Onrep_Bleed()
{
	SetActorLocationAndRotation(activePos, activeRot.Quaternion());
	niagara->Activate(true);
}

void ABleedingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABleedingActor, activePos);
	DOREPLIFETIME(ABleedingActor, activeRot);
}

// Called when the game starts or when spawned
//void ABleedingActor::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ABleedingActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

