// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/LevelPlace.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>


ALevelPlace::ALevelPlace()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	setLevelArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Level Area"));
	setLevelArea->SetupAttachment(RootComponent);
}


void ALevelPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

