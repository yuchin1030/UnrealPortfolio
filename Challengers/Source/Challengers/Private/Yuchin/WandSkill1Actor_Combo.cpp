// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandSkill1Actor_Combo.h"
#include "OurGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

AWandSkill1Actor_Combo::AWandSkill1Actor_Combo()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWandSkill1Actor_Combo::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
}

void AWandSkill1Actor_Combo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWandSkill1Actor_Combo::WandSkill1_Combo()
{
	ServerRPC_WandSkill1_Combo();
}

void AWandSkill1Actor_Combo::ServerRPC_WandSkill1_Combo_Implementation()
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(400), params);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 400, 12, FColor::Blue, false, 5, 0, 1);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			if (gi)
			{
				gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic1", ""))->DamagePower * damagePercent * gi->buffWandDamagePercent;
				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);

				MultiRPC_WandSkill1_Combo(hitsArr[i].ImpactPoint);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkill1_Combo : Not Enemy"));
		}
	}
}

void AWandSkill1Actor_Combo::MultiRPC_WandSkill1_Combo_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}
