// Fill out your copyright notice in the Description page of Project Settings.


#include "Wand.h"
#include "../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Yuchin/WandSkill1SpawnActor.h"
#include "Yuchin/WandSkill2Actor.h"
#include "Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "Net/UnrealNetwork.h"
#include "ChallengersCharacter.h"

AWand::AWand()
{
	PrimaryActorTick.bCanEverTick = true;

	wandMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wandMeshComp"));

	SetRootComponent(wandMeshComp);
	WeaponEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Weapon Effect"));
	WeaponEffect->SetupAttachment(wandMeshComp);
	WeaponEffect->SetRelativeLocation(FVector(-10, 0, 60));
}

void AWand::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	WeaponEffect->SetRelativeScale3D(EffectWandScale);
}

void AWand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//currentTime += DeltaTime;

	//if (bWandSkill1)
	//{
	//	stopTime += DeltaTime;
	//}

	//if (bWandSkill1 && currentTime > delayTime)
	//{
	//	WandSkill1(_curForward, _curLoc);
	//
	//}

	//if (stopTime > 3.0f)
	//{
	//	bWandSkill1 = false;
	//	stopTime = 0;
	//}
}
//
//void AWand::WandBasicAttack(FVector _basicLoc)
//{
//	ServerRPC_WandBasicAttack(_basicLoc);
//}

void AWand::ServerRPC_WandBasicAttack_Implementation(FVector _basicLoc, AChallengersCharacter* player)
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, _basicLoc, _basicLoc, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(200), params);

	//MultiRPC_WandBasicAttack(_basicLoc);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			FVector enemyLoc = hitsArr[i].ImpactPoint;

			if (gi)
			{
				// player->currentWeaponStat[1] : weaponAttackPower
				gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("MagicBasic", ""))->DamagePower + player->currentWeaponStat[1] * gi->buffWandDamagePercent;

				UGameplayStatics::PlaySound2D(GetWorld(), wandBasicHitSound);

				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);
			}

			

			auto* fx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), basicHitVFX, enemyLoc);

			
			if (fx)
			{
				FTimerHandle TimerHandle;

				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([=]() {
					fx->DestroyComponent();
				});

				GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkillBasic : Not Enemy"));
		}
	}
}

//void AWand::MultiRPC_WandBasicAttack_Implementation(FVector basicLoc_)
//{
//	//DrawDebugSphere(GetWorld(), basicLoc_, 200, 12, FColor::Red, false, 2, 0, 1);
//}

void AWand::WandSkill1(FVector curForward, FVector curLoc)
{
	//float XLoc = (_curForward * 500).X + _curLoc.X;
	//float YLoc = (_curForward * 500).Y + _curLoc.Y;
	//float randomX = UKismetMathLibrary::RandomFloatInRange(0, 250);
	//float randomY = UKismetMathLibrary::RandomFloatInRange(0, 250);

	//FVector spawnedLoc = FVector(XLoc + randomX, YLoc + randomY, 500);
}

//void AWand::ServerRPC_WandSkill1_Implementation(FVector curForward, FVector curLoc, AChallengersCharacter* player)
//{
//	_curForward = curForward;
//	_curLoc = curLoc;
//
//	//bWandSkill1 = true;
//	
//	FActorSpawnParameters params;
//
//	if (skill1Actor_bp != nullptr)
//	{
//		skill1Actor = GetWorld()->SpawnActor<AWandSkill1SpawnActor>(skill1Actor_bp, curLoc + curForward * 800.0f, FRotator(0), params);
//	}
//
//	//MultiRPC_WandSkill1(_curForward, _curLoc);
//
//	if (skill1Actor)
//	{
//		player->ServerRPC_SetSkillPointsDmgPercent(3);
//		skill1Actor->ServerRPC_WandSkill1Hit();
//	}
//	
//}
//
//void AWand::MultiRPC_WandSkill1_Implementation(FVector curForward_, FVector curLoc_)
//{
//	
//}

void AWand::WandSkill2()
{
	UE_LOG(LogTemp, Warning, TEXT("WandSkill2"));
}

void AWand::ServerRPC_WandSkill2_Implementation(FVector curLoc, AChallengersCharacter* player)
{
	/*FTimerHandle hdl;
	GetWorldTimerManager().SetTimer(hdl, [&] {
	}, 2, false);*/

		MultiRPC_WandSkill2(curLoc);

	if (skill2Actor != nullptr)
	{
		player->ServerRPC_SetSkillPointsDmgPercent(4);
		// 이건 이펙트 자체 액터
		skill2Actor->ServerRPC_WandSkill2();

	}
}

void AWand::MultiRPC_WandSkill2_Implementation(FVector curLoc_)
{
	FActorSpawnParameters params;

	if (skill2Actor_bp != nullptr)
	{
		skill2Actor = GetWorld()->SpawnActor<AWandSkill2Actor>(skill2Actor_bp, curLoc_, FRotator(0), params);
	}

}

void AWand::WandSkill3()
{
	UE_LOG(LogTemp, Warning, TEXT("WandSkill3"));
}

void AWand::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWand, basicHitVFX);
}

void AWand::UpgradeWandEffect(int32 weaponLevel)
{
	if (weaponLevel <= 1)
	{
		EffectWandScale = FVector(0, 0, 0);
	}
	else if (weaponLevel <= 10)
	{
		EffectWandScale = FVector(0.3, 0.3, 0.3);
	}
	else if (weaponLevel <= 19)
	{
		EffectWandScale = FVector(0.6, 0.6, 0.6);
	}
	else
	{
		EffectWandScale = FVector(1.0, 1.0, 1.0);
	}

	WeaponEffect->SetRelativeScale3D(EffectWandScale);
}
