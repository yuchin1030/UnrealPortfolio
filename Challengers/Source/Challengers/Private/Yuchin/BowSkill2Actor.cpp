// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/BowSkill2Actor.h"
#include "../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include "Net/UnrealNetwork.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "ChallengersCharacter.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

ABowSkill2Actor::ABowSkill2Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	fx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx"));
	fx->SetupAttachment(defaultSceneRoot);

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComp->SetupAttachment(fx);

	fx->SetRelativeLocation(FVector(-260, 0, 0));
	fx->SetRelativeScale3D(FVector(1));

	boxComp->SetRelativeLocation(FVector(-50, 0, 0));
	boxComp->SetBoxExtent(FVector(270, 97, 67));

}

void ABowSkill2Actor::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABowSkill2Actor::OnFxBeginOverlap);

	FTimerHandle destroyHdl;
	GetWorldTimerManager().SetTimer(destroyHdl, [&] {
		Destroy();
	}, 1.0f, false);

	/*cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	startLoc = cc->GetFollowCamera()->GetForwardVector();*/
}

void ABowSkill2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fx != nullptr)
		{
			fx->SetWorldLocation(fx->GetComponentLocation() + fx->GetForwardVector() * speed * speedCorrect * DeltaTime);
		}

}

void ABowSkill2Actor::SetDamageGage(float damageGage)
{
	ServerRPC_SetDamageGage(damageGage);
}

void ABowSkill2Actor::ServerRPC_SetDamageGage_Implementation(float _damageGage)
{
	damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Gun2", ""))->DamagePower + (weaponAttackPower * damagePercent);

	if (_damageGage >= 0 && _damageGage <= 40)
	{
		scale = FVector(1, 0.4, 0.4);
		//fx->SetWorldScale3D(scale);
		damageValue = 1;
	}
	else if (_damageGage <= 99)
	{
		scale = FVector(2, 0.8, 0.8);
		//fx->SetWorldScale3D(scale);
		damageValue = 1.4;
	}
	else
	{
		scale = FVector(5, 2, 2);
		//fx->SetWorldScale3D(scale);
		damageValue = 2;
	}

	OnRep_ChangeScale();

	//damage *= damageValue;
}

void ABowSkill2Actor::OnRep_ChangeScale()
{
	fx->SetWorldScale3D(scale);
}

void ABowSkill2Actor::OnFxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		//FMath::InterpEaseInOut(0, 1, sec, 2)
		if (OtherActor->ActorHasTag("Enemy"))
		{
			if (gi)
			{
				gi->bowDamage = damage * damageValue * gi->buffBowDamagePercent;
				UGameplayStatics::ApplyDamage(OtherActor, gi->bowDamage, nullptr, nullptr, nullptr);
			}

			ServerRPC_ApplyDamage(OtherActor->GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowSkill2 : Not Enemy"));
		}

	}
}

void ABowSkill2Actor::ServerRPC_ApplyDamage_Implementation(FVector hitLoc)
{
	MultiRPC_ApplyDamage(hitLoc);
}

void ABowSkill2Actor::MultiRPC_ApplyDamage_Implementation(FVector _hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _hitLoc);
}

void ABowSkill2Actor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABowSkill2Actor, scale);
}