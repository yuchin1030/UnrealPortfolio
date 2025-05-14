// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "ChallengersCharacter.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BleedingActor.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	weaponBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBody"));
	weaponBody->SetupAttachment(rootComp);

	attackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	attackCollision->SetupAttachment(weaponBody);
	attackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;

	Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SetOwner(GetWorld()->GetFirstPlayerController());

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	attackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::WeaponHit);

	MakeBleed();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::dataInit(FName _rowName, bool bIsWeapon1, ABaseEnemy* ownedEnemy)
{
	ServerRPC_dataInit(_rowName, bIsWeapon1, ownedEnemy);
}

void ABaseWeapon::ServerRPC_dataInit_Implementation(FName _rowName, bool bIsWeapon1, class ABaseEnemy* ownedEnemy)
{
	enemyREF = ownedEnemy;
	rowName = _rowName;
	if (gi) {
		if (bIsWeapon1) {
			weaponStat = *(gi->DT_Weapon1Data->FindRow<FweaponSpec>(rowName, ""));
		}
		else {
			weaponStat = *(gi->DT_Weapon2Data->FindRow<FweaponSpec>(rowName, ""));
		}
		atkMoveNum = weaponStat.attackSelector.Num() - 1;
	}
}

void ABaseWeapon::ActiveDmgBox()
{
	attackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UGameplayStatics::PlaySound2D(GetWorld(), swingSound);
}

void ABaseWeapon::DeactiveDmgBox()
{
	attackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseWeapon::MakeBleed()
{
	ServerRPC_MakeBleed();
}

void ABaseWeapon::ServerRPC_MakeBleed_Implementation()
{
	bleed = GetWorld()->SpawnActor<ABleedingActor>(bleed_bp, FVector(0.0f), FRotator::ZeroRotator);
}

void ABaseWeapon::ClearBleed()
{
	ServerRPC_ClearBleed();
}

void ABaseWeapon::ServerRPC_ClearBleed_Implementation()
{
	if (bleed) {
		bleed->Destroy();
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([&]() {
		UE_LOG(LogTemp, Warning, TEXT("nextTick"));
		Destroy();
		}));
}

void ABaseWeapon::WeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(OtherActor);
	if (player)
	{
		if (enemyREF)
		{
			AController* enemyController = enemyREF->GetController();
			float atkResult = UGameplayStatics::ApplyDamage(player, weaponStat.damage, enemyController, enemyREF, damageType);
			UGameplayStatics::PlaySound2D(GetWorld(), hitSound);
			if (bleed) {
				bleed->ActiveBleed(player->GetActorLocation(), GetActorLocation());
			}
			if (atkResult <= 0.0f)
			{
				enemyREF->AIState = EAttackState::IDLE;
				enemyREF->FindPlayer();
			}
			UE_LOG(LogTemp, Warning, TEXT("Player HIT!"));
			DeactiveDmgBox();
		}
	}
}

