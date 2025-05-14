// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/BowSkill1Actor.h"
#include "Components/BoxComponent.h"
#include "CHR/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include "ChallengersCharacter.h"
#include "../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "Net/UnrealNetwork.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

ABowSkill1Actor::ABowSkill1Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	fx1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx1"));
	fx2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx2"));
	fx3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fx3"));

	fx1->SetupAttachment(defaultSceneRoot);
	fx2->SetupAttachment(defaultSceneRoot);
	fx3->SetupAttachment(defaultSceneRoot);

	boxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp1"));
	boxComp2 = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp2"));
	boxComp3 = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp3"));

	fx1->SetRelativeLocation(FVector(20, 0, 0));

	fx2->SetRelativeLocation(FVector(-20.958103, -101.084796, 0));
	fx2->SetRelativeRotation(FRotator(0, -24.418271, 0));

	fx3->SetRelativeLocation(FVector(-20.958103, 101.084796, 0));
	fx3->SetRelativeRotation(FRotator(0, 24.418271, 0));

	fx1->SetRelativeScale3D(FVector(1, 0.3, 0.3));
	fx2->SetRelativeScale3D(FVector(1, 0.3, 0.3));
	fx3->SetRelativeScale3D(FVector(1, 0.3, 0.3));

	boxComp1->SetupAttachment(fx1);
	boxComp2->SetupAttachment(fx2);
	boxComp3->SetupAttachment(fx3);

	boxComp1->SetRelativeLocation(FVector(-50, 0, 0));
	boxComp2->SetRelativeLocation(FVector(-50, 0, 0));
	boxComp3->SetRelativeLocation(FVector(-50, 0, 0));

	boxComp1->SetBoxExtent(FVector(90, 58, 32));
	boxComp2->SetBoxExtent(FVector(90, 58, 32));
	boxComp3->SetBoxExtent(FVector(90, 58, 32));

	boxComp1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	boxComp2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	boxComp3->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABowSkill1Actor::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	//speedCorrect = FMath::InterpEaseInOut(0, 1, DeltaTime, 2);
	
	//this->OnActorBeginOverlap.AddDynamic(this, &ABowSkill1Actor::OnArrowBeginOverlap);
	boxComp1->OnComponentBeginOverlap.AddDynamic(this, &ABowSkill1Actor::OnFx1BeginOverlap);
	boxComp2->OnComponentBeginOverlap.AddDynamic(this, &ABowSkill1Actor::OnFx2BeginOverlap);
	boxComp3->OnComponentBeginOverlap.AddDynamic(this, &ABowSkill1Actor::OnFx3BeginOverlap);
		
}

void ABowSkill1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (fx1 != nullptr)
		fx1->SetWorldLocation(fx1->GetComponentLocation() + fx1->GetForwardVector() * speed * speedCorrect * DeltaTime);

	if (fx2 != nullptr)
		fx2->SetWorldLocation(fx2->GetComponentLocation() + fx2->GetForwardVector() * speed * speedCorrect * DeltaTime);

	if (fx3 != nullptr)
		fx3->SetWorldLocation(fx3->GetComponentLocation() + fx3->GetForwardVector() * speed * speedCorrect * DeltaTime);

}

void ABowSkill1Actor::OnFx1BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			ServerRPC_ApplyDamage(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowSkill1 : Not Enemy"));
		}
		
	}
}



void ABowSkill1Actor::OnFx2BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			ServerRPC_ApplyDamage(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowSkill1 : Not Enemy"));
		}

	}
}

void ABowSkill1Actor::OnFx3BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		//FMath::InterpEaseInOut(0, 1, sec, 2)
		if (OtherActor->ActorHasTag("Enemy"))
		{
			ServerRPC_ApplyDamage(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BowSkill1 : Not Enemy"));
		}

	}
}

void ABowSkill1Actor::ArrowActivate(bool bActivate)
{
	SetOwner(GetWorld()->GetFirstPlayerController());

	ServerRPC_ArrowActivate(bActivate);
}

void ABowSkill1Actor::ServerRPC_ArrowActivate_Implementation(bool bActivate)
{
	bIsActive = bActivate;

	UE_LOG(LogTemp, Warning, TEXT("ServerRPC bActivate : %d"), bIsActive);

	if (bIsActive)
	{
		fx1->Activate();
		fx2->Activate();
		fx3->Activate();

		boxComp1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		boxComp2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		boxComp3->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		speed = 1000;

		FTimerHandle destroyHdl;
		GetWorldTimerManager().SetTimer(destroyHdl, [&] {
			ArrowActivate(false);
			player->ServerRPC_SetArrow1Pool(this);
			}, 1.0f, false);

		UE_LOG(LogTemp, Warning, TEXT("active arrow1"));

	}
	else
	{
		fx1->Deactivate();
		fx2->Deactivate();
		fx3->Deactivate();

		boxComp1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		boxComp2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		boxComp3->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		speed = 0;

		fx1->SetRelativeLocation(FVector(20, 0, 0));
		fx2->SetRelativeLocation(FVector(-20.958103, -101.084796, 0));
		fx3->SetRelativeLocation(FVector(-20.958103, 101.084796, 0));

		UE_LOG(LogTemp, Warning, TEXT("deactive arrow1"));

	}

}

void ABowSkill1Actor::ServerRPC_ApplyDamage_Implementation(AActor* _OtherActor)
{
	if (gi)
	{
		gi->bowDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Gun1", ""))->DamagePower + (weaponAttackPower * damagePercent * gi->buffBowDamagePercent);
		UGameplayStatics::ApplyDamage(_OtherActor, gi->bowDamage, nullptr, nullptr, nullptr);
	}

	// 화살 비활성화
	ArrowActivate(false);
	
	MultiRPC_ApplyDamage(_OtherActor->GetActorLocation());
}

void ABowSkill1Actor::MultiRPC_ApplyDamage_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}

void ABowSkill1Actor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 에너미 체력 동기화
	DOREPLIFETIME(ABowSkill1Actor, bIsActive);
}