// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandSkill3Actor.h"
#include "ChallengersCharacter.h"
#include "OurGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

#define ATKTIME 1.5f

AWandSkill3Actor::AWandSkill3Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	fx1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx1"));
	fx2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx2"));
	fx3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx3"));
	fx4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx4"));
	fx5 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx5"));

	SetRootComponent(sceneComp);
	fx1->SetupAttachment(sceneComp);
	fx2->SetupAttachment(sceneComp);
	fx3->SetupAttachment(sceneComp);
	fx4->SetupAttachment(sceneComp);
	fx5->SetupAttachment(sceneComp);

	fx2->SetRelativeLocation(FVector(0,0,20));
	fx3->SetRelativeLocation(FVector(0, 0, -20));
	fx4->SetRelativeLocation(FVector(0, 40, 0));
	fx5->SetRelativeLocation(FVector(0, -40, 0));

	fx1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	fx2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	fx3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	fx4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	fx5->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AWandSkill3Actor::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	bDamaging = true;

}

void AWandSkill3Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWandSkill3Actor::WandSkill3(FVector start, FVector end, AChallengersCharacter* playerChar)
{
	FVector _start = start;
	FVector _end = end;

	_end.Z = 0;

	ServerRPC_WandSkill3(_start, _end, playerChar);

	//FTimerHandle timer;
	//GetWorldTimerManager().SetTimer(timer, [&] {
	//	UE_LOG(LogTemp, Warning, TEXT("Destroy"));

	//	Destroy();
	//}, 0.5f, false);
}

void AWandSkill3Actor::ServerRPC_WandSkill3_Implementation(FVector start_, FVector end_, class AChallengersCharacter* playerChar_)
{
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(playerChar_);

	GetWorld()->LineTraceMultiByChannel(hitsArr, start_, end_, ECollisionChannel::ECC_GameTraceChannel1, params);

	//DrawDebugLine(GetWorld(), _start, _end, FColor::Green, false, 5.0f);
	if (bIsAbleAtk)
	{
		for (int i = 0; i < hitsArr.Num(); i++)
		{
			if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
			{
				UE_LOG(LogTemp, Warning, TEXT("Enemy"));

				if (gi)
				{
					gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic3", ""))->DamagePower + (weaponAttackPower * damagePercent * gi->buffWandDamagePercent);
					UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), gi->wandDamage, nullptr, nullptr, nullptr);

					MultiRPC_WandSkill3(hitsArr[i].ImpactPoint);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Enemy"));
			}
		}
		bIsAbleAtk = false;
		FTimerHandle resetAtk;
		GetWorld()->GetTimerManager().SetTimer(resetAtk, FTimerDelegate::CreateLambda([&](){
			bIsAbleAtk = true;
		}), ATKTIME, false);
	}
}

void AWandSkill3Actor::MultiRPC_WandSkill3_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}

void AWandSkill3Actor::WandSkill3Activate(bool bActivate)
{
	//UE_LOG(LogTemp, Warning, TEXT("%d"));

	fx1->SetVisibility(bActivate);
	fx2->SetVisibility(bActivate);
	fx3->SetVisibility(bActivate);
	fx4->SetVisibility(bActivate);
	fx5->SetVisibility(bActivate);

	if (bActivate)
	{
		fx1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		fx2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		fx3->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		fx4->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		fx5->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		UE_LOG(LogTemp, Warning, TEXT("active wandskill3"));

	}
	else
	{
		fx1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		fx2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		fx3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		fx4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		fx5->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		SetActorLocation(FVector(0));
		UE_LOG(LogTemp, Warning, TEXT("wandSkill3Actor_var : %f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	}
}