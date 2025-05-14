// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandSkill1SpawnActor.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "CHR/BaseEnemy.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"

AWandSkill1SpawnActor::AWandSkill1SpawnActor()
{
	PrimaryActorTick.bCanEverTick = true;

	fxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fxComp"));
	SetRootComponent(fxComp);
	fxComp->SetRelativeScale3D(FVector(1.5));

	
}

void AWandSkill1SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	
	//UE_LOG(LogTemp, Warning, TEXT("WandSkill1Hit Enemy"));

	//fxComp->SetGenerateOverlapEvents(true);
	//fxComp->OnSystemFinished.AddDynamic(this, &AWandSkill1SpawnActor::Test);
	//this->OnActorBeginOverlap.AddDynamic(this, &AWandSkill1SpawnActor::ServerRPC_WandSkill1Hit);
}

void AWandSkill1SpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWandSkill1SpawnActor::ServerRPC_WandSkill1Hit_Implementation()
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(450.0f), params);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 450, 12, FColor::Purple, false, 15, 0, 1);

	for (int i = 0; i < hitsArr.Num(); i++)
	{
		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkill1 : Enemy"));

			FVector enemyLoc = hitsArr[i].ImpactPoint;

			MultiRPC_WandSkill1Hit(enemyLoc);

			if (gi)
			{
				gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic1", ""))->DamagePower + (weaponAttackPower * damagePercent * gi->buffWandDamagePercent);
				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);

				MultiRPC_WandSkill1Hit(enemyLoc);
			}
		
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WandSkill1 : Not Enemy"));
		}
	}
}

void AWandSkill1SpawnActor::MultiRPC_WandSkill1Hit_Implementation(FVector _enemyLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _enemyLoc);
}

