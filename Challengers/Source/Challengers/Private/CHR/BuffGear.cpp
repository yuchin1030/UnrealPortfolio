// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BuffGear.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"

void ABuffGear::ActivateGear()
{
	FTimerHandle buffEnd;
	switch (buffNum)
	{
	case 0:
		if (enemyREF->weapon1)
		{
			enemyREF->weapon1->weaponStat.damage *= buffPower;
		}
		if (enemyREF->weapon2)
		{
			enemyREF->weapon2->weaponStat.damage *= buffPower;
		}

		GetWorld()->GetTimerManager().SetTimer(buffEnd, FTimerDelegate::CreateLambda([&]() {
			if (enemyREF->weapon1)
			{
				enemyREF->weapon1->weaponStat.damage /= buffPower;
			}
			if (enemyREF->weapon2)
			{
				enemyREF->weapon2->weaponStat.damage /= buffPower;
			}
		}), activeTime, false);

		break;
	case 1:
		gearEffectComp->SetRelativeLocation(FVector(0.0f, 0.0f, enemyREF->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		enemyREF->enemySpec.totalDEF *= buffPower;

		GetWorld()->GetTimerManager().SetTimer(buffEnd, FTimerDelegate::CreateLambda([&]() {
			enemyREF->enemySpec.totalDEF /= buffPower;
		}), activeTime, false);

		break;
	default:
		break;
	}
	gearEffectComp->Activate(true);
	enemyREF->GetMesh()->SetOverlayMaterial(gearStat.overlayMat);
	activeTime = 0.0f;
}
