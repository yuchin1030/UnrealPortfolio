// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/Arrow.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ChildActorComponent.h"
#include "Yuchin/BowSkill1Actor.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	VFXActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("VFXActor"));

	SetRootComponent(VFXActor);
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();

	bowSkill1Actor = Cast<ABowSkill1Actor>(VFXActor->GetChildActor());

}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

