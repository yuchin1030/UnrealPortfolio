// Fill out your copyright notice in the Description page of Project Settings.


#include "Koopa_ball.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>

// Sets default values
AKoopa_ball::AKoopa_ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
}

// Called when the game starts or when spawned
void AKoopa_ball::BeginPlay()
{
	Super::BeginPlay();
	moveDirection = GetActorForwardVector();
	SetLifeSpan(2.0f);
}

// Called every frame
void AKoopa_ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + moveDirection * moveSpeed * DeltaTime);
}

