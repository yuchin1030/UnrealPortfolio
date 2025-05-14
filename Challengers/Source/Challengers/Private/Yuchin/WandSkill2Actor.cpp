// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandSkill2Actor.h"
#include "Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

// Sets default values
AWandSkill2Actor::AWandSkill2Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWandSkill2Actor::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	
	FTimerHandle destroyHdl;
	GetWorldTimerManager().SetTimer(destroyHdl, [&] {
		Destroy();
	}, 5, false);
}

// Called every frame
void AWandSkill2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWandSkill2Actor::WandSkill2()
{
	

	
}

void AWandSkill2Actor::ServerRPC_WandSkill2_Implementation()
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(450.0f), params);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkill2 : Enemy"));

			if (gi)
			{
				gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic2", ""))->DamagePower + (weaponAttackPower * damagePercent * gi->buffWandDamagePercent);
				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);

				MultiRPC_WandSkill2(hitsArr[i].ImpactPoint);
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkill2 : Not Enemy"));
		}
	}

}

void AWandSkill2Actor::MultiRPC_WandSkill2_Implementation(FVector _enemyLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _enemyLoc);
}

