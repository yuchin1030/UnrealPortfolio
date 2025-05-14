// Fill out your copyright notice in the Description page of Project Settings.


#include "WandSkill1Actor_Completed.h"
#include "OurGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

AWandSkill1Actor_Completed::AWandSkill1Actor_Completed()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWandSkill1Actor_Completed::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
}

void AWandSkill1Actor_Completed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWandSkill1Actor_Completed::WandSkill1()
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(450.0f), params);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 450, 12, FColor::Blue, false, 5, 0, 1);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			if (gi)
			{
				gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic3", ""))->DamagePower * damagePercent * gi->buffWandDamagePercent * 2;
				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);

				ServerRPC_WandSkill1(hitsArr[i].ImpactPoint);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Enemy"));
		}
	}
}

void AWandSkill1Actor_Completed::ServerRPC_WandSkill1_Implementation(FVector hitLoc)
{
	MultiRPC_WandSkill1(hitLoc);
}

void AWandSkill1Actor_Completed::MultiRPC_WandSkill1_Implementation(FVector _hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _hitLoc);
}
