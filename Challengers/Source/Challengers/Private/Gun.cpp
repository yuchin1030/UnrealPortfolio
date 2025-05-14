// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "OurGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(76.862251, 19.348581, 9.855666));

	fxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fxComp"));
	fxComp->SetupAttachment(boxComp);
	fxComp->SetRelativeLocation(FVector(50, 0, 0));
	fxComp->SetRelativeScale3D(FVector(0.685, 0.413897, 0.186254));

}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AGun::GunBasicAttack);

	enemies.Empty();

	//startLoc = cc->GetFollowCamera()->GetForwardVector();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * 5000 * DeltaTime, true);

	if (UKismetSystemLibrary::IsValid(fxComp))
	{
		FTimerHandle destroyHdl;
		GetWorldTimerManager().SetTimer(destroyHdl, [&] {
			Destroy();
		}, 1.0f, false);

	}

}

void AGun::GunBasicAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Enemy") && !enemies.Contains(OtherActor))
		{
			ServerRPC_GunBasicAttack(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowBasic : Not Enemy"));
		}
	}

}

void AGun::ServerRPC_GunBasicAttack_Implementation(AActor* _OtherActor)
{
	boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogTemp, Warning, TEXT("bHitGunBasic : %d"), bHitGunBasic);

		enemies.Add(_OtherActor);

		if (gi && false == bHitGunBasic)
		{
			bHitGunBasic = true;
			gi->bowDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("GunBasic", ""))->DamagePower + weaponAttackPower * gi->buffBowDamagePercent;
			UGameplayStatics::ApplyDamage(_OtherActor, gi->bowDamage, nullptr, nullptr, nullptr);
		}

		MultiRPC_GunBasicAttack(_OtherActor->GetActorLocation());

		Destroy();
	
}

void AGun::MultiRPC_GunBasicAttack_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}