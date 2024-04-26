// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet_koopaHat.h"

// Sets default values
ABullet_koopaHat::ABullet_koopaHat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullet_koopaHat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet_koopaHat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABullet_koopaHat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

