// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootGear.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BaseBullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"

void AShootGear::DataInit(FName _rowName, bool bIsWeapon1, ABaseEnemy* ownedEnemy)
{
	Super::DataInit(_rowName, bIsWeapon1, ownedEnemy);

	FActorSpawnParameters params;
	params.Owner = GetWorld()->GetFirstPlayerController();
	params.Instigator = GetInstigator();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < 8; i++)
	{
		ABaseBullet* shootREF = GetWorld()->SpawnActor<ABaseBullet>(gearStat.shootActor, FVector::ZeroVector, FRotator::ZeroRotator, params);
		if (shootREF) {
			shootREF->niagara->SetVisibility(false);
			shootREF->bIsActive = false;
			shootREF->hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			shootREF->DataInit(damage, nullptr);
			bulletArray.Add(shootREF);
		}
	}
}

void AShootGear::ActivateGear()
{
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_ShootBullet();
}

void AShootGear::ServerRPC_ShootBullet_Implementation()
{
	FRotator shootRot = enemyREF->GetActorForwardVector().Rotation();

	for (int i = 0; i < 8; i++)
	{
		bulletArray[i]->SetActorRotation(shootRot);
		
		bulletArray[i]->BulletActivate(enemyREF->GetActorLocation() + bulletArray[i]->GetActorForwardVector() * 150, shootRot);

		shootRot.Yaw += 45.0f;
	}

}
