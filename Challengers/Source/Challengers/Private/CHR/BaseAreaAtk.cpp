// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseAreaAtk.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"
#include "CHR/WarningCircleActor.h"
#include "CHR/BaseEnemy.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>

// Sets default values
ABaseAreaAtk::ABaseAreaAtk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	hitColl = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	hitColl->SetupAttachment(rootComp);
	hitColl->SetSphereRadius(atkRadius);
	hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	niagara->SetupAttachment(rootComp);
	niagara->bAutoActivate = false;
	//niagara->SetWorldScale3D(FVector(0.5f));

	playingLoop = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopSound"));
	playingLoop->SetupAttachment(rootComp);
	playingLoop->bAutoActivate = false;

	Tags.Add(FName("Enemy"));

}

// Called when the game starts or when spawned
void ABaseAreaAtk::BeginPlay()
{
	Super::BeginPlay();
	
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_SpawnWarning();
	
	if (HasAuthority() && warningCircle) {
		warningCircle->warningTimeEndDelegate.BindUFunction(this, FName("WarningEnd"));
	}

	atkTime = activeTime/atkCount;
	hitColl->SetSphereRadius(atkRadius);

	hitColl->OnComponentBeginOverlap.AddDynamic(this, &ABaseAreaAtk::OnOverlaped);
}

// Called every frame
void ABaseAreaAtk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//경고타임이 끝나고, 데미지가 가해지는 시간
	if (!bIsWarning && currentTime < activeTime) {
		currentTime = FMath::Min(currentTime + DeltaTime, activeTime);

		if (nextAtkTime == 0.0f || currentTime > nextAtkTime)
		{
			TArray<FHitResult> hitInfos;
			FCollisionQueryParams queryParams;
			queryParams.AddIgnoredActor(this);
			bool bResult = GetWorld()->SweepMultiByChannel(hitInfos, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(atkRadius), queryParams);
			if (bResult) {
				for (auto& hit : hitInfos) {
					AChallengersCharacter* player = Cast<AChallengersCharacter>(hit.GetActor());
					if (player != nullptr && hit.GetComponent()->GetName().Contains("CollisionCylinder")) {
						float atkResult = UGameplayStatics::ApplyDamage(player, damage, nullptr, nullptr, damageType);
						if (atkResult <= 0.0f)
						{
							if(enemyREF)
							{
								enemyREF->AIState = EAttackState::IDLE;
								enemyREF->FindPlayer();
							}
						}
					}
				}
			}
			nextAtkTime += atkTime;
		}
	}
	//데미지가 가해지는 시간도 지나고 이펙트 제거 및 액터 정리과정
	else if (!bIsWarning) {
		if (!bIsEnd)
		{
			SetOwner(GetWorld()->GetFirstPlayerController());
			ServerRPC_DeactiveEffect();
			GetWorld()->GetTimerManager().SetTimer(destroyTimer, FTimerDelegate::CreateLambda([&](){
				ClearEffect();
			}), 2.0f, false);
			bIsEnd = true;
		}
		else{
			if (GetWorld()->GetTimerManager().IsTimerActive(destroyTimer))
			{
				playingLoop->SetVolumeMultiplier(FMath::Lerp(1.0f, 0.0f, (GetWorld()->GetTimerManager().GetTimerElapsed(destroyTimer)) / 2.0f));
			}
		}
	}
}

void ABaseAreaAtk::ClearEffect()
{
	bIsWarning = true;
	playingLoop->Stop();
	currentTime = 0.0f;
	nextAtkTime = 0.0f;
	bIsEnd = false;
	hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseAreaAtk::DataInit(float _damage, ABaseEnemy* shooter)
{
	damage = _damage;
	enemyREF = shooter;
}

void ABaseAreaAtk::StartAtk(FVector AtkLoc)
{
	ServerRPC_StartAtk(AtkLoc);
	ServerRPC_ActiveWarning();
}

void ABaseAreaAtk::ServerRPC_StartAtk_Implementation(FVector AtkLoc)
{
	hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorLocation(AtkLoc);
}

void ABaseAreaAtk::ServerRPC_SpawnWarning_Implementation()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	warningCircle = GetWorld()->SpawnActor<AWarningCircleActor>(warningCircle_BP, GetActorLocation(), FRotator::ZeroRotator, params);
	warningCircle->Init(size, warningTime);
}

void ABaseAreaAtk::ServerRPC_ActiveWarning_Implementation()
{
	warningCircle->WarningActivate(GetActorLocation());
}

void ABaseAreaAtk::WarningEnd()
{
	currentTime = 0.0f;
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_ActiveEffect();
	playingLoop->SetVolumeMultiplier(1.0f);
	playingLoop->Play();
	bIsWarning = false;
	hitColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABaseAreaAtk::ServerRPC_ActiveEffect_Implementation()
{
	MultiRPC_ActiveEffect();
}

void ABaseAreaAtk::MultiRPC_ActiveEffect_Implementation()
{
	niagara->Activate(true);
}

void ABaseAreaAtk::ServerRPC_DeactiveEffect_Implementation()
{
	MultiRPC_DeactiveEffect();
}

void ABaseAreaAtk::MultiRPC_DeactiveEffect_Implementation()
{
	niagara->Deactivate();
}

void ABaseAreaAtk::EraseWarning()
{
	ServerRPC_EraseWarning();
}

void ABaseAreaAtk::ServerRPC_EraseWarning_Implementation()
{
	warningCircle->Destroy();
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([&](){
		Destroy();
	}));
}

void ABaseAreaAtk::OnOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsWarning) {
		if (OtherActor->ActorHasTag(FName("Enemy"))) {
			return;
		}
		AChallengersCharacter* player = Cast<AChallengersCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Something HIT!"));
		if (player)
		{
			float atkResult = UGameplayStatics::ApplyDamage(player, damage, nullptr, nullptr, damageType);
			if (atkResult <= 0.0f)
			{
				if (enemyREF) {
					enemyREF->AIState = EAttackState::IDLE;
					enemyREF->FindPlayer();
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Player HIT!"));
		}
	}
}

void ABaseAreaAtk::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAreaAtk, currentTime);
}
