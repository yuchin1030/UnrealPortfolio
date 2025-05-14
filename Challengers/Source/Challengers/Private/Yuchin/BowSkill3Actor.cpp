// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/BowSkill3Actor.h"
#include "OurGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

ABowSkill3Actor::ABowSkill3Actor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABowSkill3Actor::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	FTimerHandle destroyHdl;
	GetWorldTimerManager().SetTimer(destroyHdl, [&] {
		Destroy();
	}, 2.0f, false);
}

void ABowSkill3Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABowSkill3Actor::BowSkill3()
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(150), params);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 200, 12, FColor::Blue, false, 5, 0, 1);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			if (gi)
			{
				gi->bowDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Gun3", ""))->DamagePower + (weaponAttackPower * damagePercent * gi->buffBowDamagePercent);
				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->bowDamage, nullptr, nullptr, nullptr);

				ServerRPC_ApplyDamage(hitsArr[i].GetActor()->GetActorLocation());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowSkill3 : Not Enemy"));
		}
	}
}

void ABowSkill3Actor::ServerRPC_ApplyDamage_Implementation(FVector hitLoc)
{
	MultiRPC_ApplyDamage(hitLoc);
}

void ABowSkill3Actor::MultiRPC_ApplyDamage_Implementation(FVector _hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _hitLoc);
}

