// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/Arrow2.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ChildActorComponent.h"

AArrow2::AArrow2()
{
	PrimaryActorTick.bCanEverTick = true;

	//VFXActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("VFXActor"));

	//SetRootComponent(VFXActor);
}

void AArrow2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

