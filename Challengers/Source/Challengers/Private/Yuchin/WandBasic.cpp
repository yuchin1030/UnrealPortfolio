// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandBasic.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

#include "../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
AWandBasic::AWandBasic()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(125);

	fx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx"));
	fx->SetupAttachment(sphereComp);
	 
}

void AWandBasic::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWandBasic::WandBasicAttack);

	enemies.Empty();

}

void AWandBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);

	if (UKismetSystemLibrary::IsValid(fx))
	{
		FTimerHandle destroyHdl;
		GetWorldTimerManager().SetTimer(destroyHdl, [&] {
			Destroy();
		}, 1.0f, false);

	}

}

void AWandBasic::WandBasicAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Enemy") && !enemies.Contains(OtherActor))
		{
			ServerRPC_WandBasicAttack(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WandBasic : Not Enemy"));
		}
	}

}

void AWandBasic::ServerRPC_WandBasicAttack_Implementation(AActor* _OtherActor)
{
	sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	enemies.Add(_OtherActor);

	if (gi && false == bHitWandBasic)
	{
		bHitWandBasic = true;
		gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("MagicBasic", ""))->DamagePower + gi->buffBowDamagePercent;
		UGameplayStatics::ApplyDamage(_OtherActor, gi->wandDamage, nullptr, nullptr, nullptr);
	}

	MultiRPC_WandBasicAttack(_OtherActor->GetActorLocation());

	Destroy();

}


void AWandBasic::MultiRPC_WandBasicAttack_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}

void AWandBasic::WandBasicActivate(bool bActivate)
{
	//UE_LOG(LogTemp, Warning, TEXT("%d"));

	fx->SetVisibility(bActivate);

	if (bActivate)
	{
		fx->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		UE_LOG(LogTemp, Warning, TEXT("active wandbasic"));

	}
	else
	{
		fx->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		SetActorLocation(FVector(0));
		UE_LOG(LogTemp, Warning, TEXT("wandbasic : %f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	}
}