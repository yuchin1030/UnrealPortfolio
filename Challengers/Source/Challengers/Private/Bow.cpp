// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "Components/StaticMeshComponent.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>

// Sets default values
ABow::ABow()
{
	PrimaryActorTick.bCanEverTick = true;

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	Bow->SetupAttachment(RootComponent);
	Bow->SetRelativeScale3D(FVector(1.5, 1.5, 1.5));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Bow);
	Effect->SetRelativeScale3D(BowEffectScale);
	
}


void ABow::UpgradeBowEffect(int32 weaponLevel)
{


	if (weaponLevel <= 1)
	{
		BowEffectScale = FVector(0, 0, 0);
	}
	else if (weaponLevel <= 10)
	{
		BowEffectScale = FVector(0.3, 0.3, 0.3);
	}
	else if (weaponLevel <= 19)
	{
		BowEffectScale = FVector(0.6, 0.6, 0.6);
	}
	else
	{
		BowEffectScale = FVector(1.0, 1.0, 1.0);
	}

	Effect->SetWorldScale3D(BowEffectScale);

}
