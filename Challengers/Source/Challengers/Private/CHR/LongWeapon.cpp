// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/LongWeapon.h"
#include "CHR/BaseBullet.h"
#include "CHR/BaseAreaAtk.h"
#include "CHR/BaseEnemy.h"
#include "Net/UnrealNetwork.h"

void ALongWeapon::dataInit(FName _rowName, bool bIsWeapon1, ABaseEnemy* ownedEnemy)
{
	Super::dataInit(_rowName, bIsWeapon1, ownedEnemy);

	ServerRPC_LongDataInit(_rowName, bIsWeapon1, ownedEnemy);
}

void ALongWeapon::ServerRPC_LongDataInit_Implementation(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABaseBullet* bullet;
	for (int32 i = 0; i < bulletFireNum; i++) {
		bullet = GetWorld()->SpawnActor<ABaseBullet>(shotBP, FVector::ZeroVector, FRotator::ZeroRotator, params);
		if (bullet)
		{
			bullet->DataInit(weaponStat.damage, nullptr);
		}
		bulletArray.Add(bullet);
	}

	ABaseAreaAtk* aura;
	for (int32 i = 0; i < auraFireNum; i++) {
		aura = GetWorld()->SpawnActor<ABaseAreaAtk>(auraBP, FVector::ZeroVector, FRotator::ZeroRotator, params);
		if (aura)
		{
			aura->DataInit(weaponStat.damage, nullptr);
		}
		auraArray.Add(aura);
	}
	Tags.Add(FName("LongWeapon"));
}

void ALongWeapon::FireMagic(FVector fireLoc, FRotator fireRot, FVector targetLoc)
{
	ServerRPC_FireMagic(fireLoc, fireRot, targetLoc);
}

void ALongWeapon::ServerRPC_FireMagic_Implementation(FVector fireLoc, FRotator fireRot, FVector targetLoc)
{
	//0이 발사체, 1이 범위공격
	int32 magicSelect = FMath::RandRange(0, magicSelectNum);
	//범위공격 연속발사 방지
	if (magicSelect == 1 && bIsAreaBefore)
	{
		bIsAreaBefore = false;
		magicSelect = 0;
	}
	else if (magicSelect == 1 && !bIsAreaBefore) {
		bIsAreaBefore = true;
	}
	else {
		bIsAreaBefore = false;
	}

	switch (magicSelect)
	{
	case 0:
		newFirePos = fireLoc;
		for (int32 i = 0; i < bulletFireNum; i++) {
			FVector newFireRotVec = newFirePos - enemyREF->GetActorLocation();
			//bulletArray[i]->BulletActivate(newFirePos, fireRot);
			bulletArray[i]->BulletActivate(newFirePos, newFireRotVec.Rotation());
			newFirePos = fireLoc + FVector(FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f));
		}
		break;
	case 1:
		targetLoc.Z -= 96.0f;
		newFirePos = targetLoc;
		for (int32 i = 0; i < auraFireNum; i++) {
			auraArray[i]->StartAtk(newFirePos);
			newFirePos = targetLoc + FVector(FMath::FRandRange(-120.0f, 120.0f), FMath::FRandRange(-120.0f, 120.0f), 0);
		}
		break;
	default:
		break;
	}
}

void ALongWeapon::ClearBullet()
{
	ServerRPC_ClearBullet();
}

void ALongWeapon::ServerRPC_ClearBullet_Implementation()
{
	for (int32 i = 0; i < bulletArray.Num(); i++)
	{
		bulletArray[i]->Destroy();
	}
	
	for (int32 i = 0; i < auraArray.Num(); i++)
	{
		auraArray[i]->EraseWarning();
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([&]() {
		UE_LOG(LogTemp, Warning, TEXT("nextTick"));
		Destroy();
		}));
}

void ALongWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 에너미 체력 동기화
	DOREPLIFETIME(ALongWeapon, newFirePos);
}