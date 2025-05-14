// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseBullet.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChallengersCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "CHR/BaseEnemy.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	hitColl = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	hitColl->SetupAttachment(rootComp);
	hitColl->SetSphereRadius(16.0f);
	hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	niagara->SetupAttachment(hitColl);
	niagara->SetWorldScale3D(FVector(0.5f));
	niagara->SetVisibility(false);

	Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetOwner(GetWorld()->GetFirstPlayerController());

	hitColl->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::BulletHit);

	durationTime = duration;
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActive)
	{
		if (startFly) {
			ServerRPC_StartSpeedCorrect();
		}

		durationTime = FMath::Max(durationTime - DeltaTime, 0.0f);
		if (durationTime > 0.0f) {
			ServerRPC_BulletFly();
		}
		else {
			ServerRPC_EndBulletFly();
		}
	}
}

void ABaseBullet::ServerRPC_StartSpeedCorrect_Implementation()
{
	if (bTIsSlow_FISHold) {
		correctTime = FMath::Clamp(correctTime + GetWorld()->GetDeltaSeconds(), 0.0f, correctDuration);

		speedCorrect = FMath::Lerp(0, 1.0f, correctTime / correctDuration);

		if (correctTime == correctDuration)
		{
			startFly = false;
		}
	}
	else {
		correctTime = FMath::Clamp(correctTime + GetWorld()->GetDeltaSeconds(), 0.0f, holdDuration);

		speedCorrect = FMath::InterpEaseIn<float>(0.0f, 1.0f, correctTime / holdDuration, 5.0f);

		if (correctTime == correctDuration)
		{
			startFly = false;
		}
	}
}

void ABaseBullet::ServerRPC_BulletFly_Implementation()
{
	bulletLoc = GetActorLocation() + (GetActorForwardVector() * speedCorrect * speed * GetWorld()->GetDeltaSeconds());
	OnRep_MoveBullet();
}

void ABaseBullet::ServerRPC_EndBulletFly_Implementation()
{
	disappearTime -= GetWorld()->GetDeltaSeconds();
	alpha = FMath::Lerp(0.0f, 1.0f, disappearTime / 0.3f);
	OnRep_Disappear();
	if (FMath::Lerp(0.0f, 1.0f, disappearTime / 0.3f) <= 0.0f)
	{
		BulletDeactivate();
	}
}

void ABaseBullet::DataInit(float _damage, ABaseEnemy* shooter)
{
	damage = _damage;
	enemyREF = shooter;
}

void ABaseBullet::OnRep_MoveBullet()
{
	SetActorLocation(bulletLoc, true);
}

void ABaseBullet::OnRep_Disappear()
{
	niagara->SetFloatParameter(FName("Alpha"), alpha);
	if (alpha == 0.0f) {
		niagara->SetVisibility(false);
	}
	else if (alpha == 1.0f)
	{
		niagara->SetVisibility(true);
	}
}

void ABaseBullet::BulletHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Enemy"))) {
		return;
	}
	AChallengersCharacter* player = Cast<AChallengersCharacter>(OtherActor);
	if (player)
	{
		float atkResult = UGameplayStatics::ApplyDamage(player, damage, nullptr, nullptr, damageType);
		UGameplayStatics::PlaySound2D(GetWorld(), hitSound);
		if (atkResult <= 0.0f)
		{
			if (enemyREF != nullptr)
			{
				enemyREF->AIState = EAttackState::IDLE;
				enemyREF->FindPlayer();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Player HIT!"));
	}
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_HitEffect();
	startFly = false;
	durationTime = 0.0f;
}

void ABaseBullet::BulletActivate(FVector fireLoc, FRotator fireRot)
{
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
	ServerRPC_Activate(fireLoc, fireRot);
}

void ABaseBullet::ServerRPC_Activate_Implementation(FVector fireLoc, FRotator fireRot)
{
	SetActorLocationAndRotation(fireLoc, fireRot);
	niagara->SetVisibility(true);
	alpha = 1.0f;
	OnRep_Disappear();
	hitColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	bIsActive = true;
}

void ABaseBullet::OnRep_Appear()
{
	niagara->SetVisibility(true);
}

void ABaseBullet::BulletDeactivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet End"));
	ServerRPC_Deactivate();
}

void ABaseBullet::ServerRPC_Deactivate_Implementation()
{
	bIsActive = false;

	alpha = 0.0f;
	OnRep_Disappear();
	hitColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	disappearTime = 0.3f;
	correctTime = 0.0f;
	speedCorrect = 0.0f;
	durationTime = duration;
	startFly = true;
}

void ABaseBullet::ServerRPC_HitEffect_Implementation()
{
	MultiRPC_HitEffect();
}

void ABaseBullet::MultiRPC_HitEffect_Implementation()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitFX, GetActorLocation());
}

void ABaseBullet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseBullet, bulletLoc);
	DOREPLIFETIME(ABaseBullet, alpha);
	DOREPLIFETIME(ABaseBullet, correctTime);
	DOREPLIFETIME(ABaseBullet, bIsActive);
}
