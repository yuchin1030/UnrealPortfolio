// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "CHR/BaseEnemy.h"
#include "ChallengersCharacter.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include "Net/UnrealNetwork.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"

ASword::ASword()
{
	PrimaryActorTick.bCanEverTick = true;

	swordMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("swordMeshComp"));
	SetRootComponent(swordMeshComp);

	traceStart = CreateDefaultSubobject<UArrowComponent>(TEXT("traceStart"));
	traceStart->SetupAttachment(swordMeshComp);
	traceStart->SetRelativeLocation(FVector(0, 0, -21.561855));
	traceStart->SetRelativeRotation(FRotator(-90, 0, 0));

	traceEnd = CreateDefaultSubobject<UArrowComponent>(TEXT("traceEnd"));
	traceEnd->SetupAttachment(swordMeshComp);
	traceEnd->SetRelativeLocation(FVector((0.000002, 0, -143.817795)));

	WeaponEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Weapon Effect"));
	WeaponEffect ->SetupAttachment(swordMeshComp);
	WeaponEffect ->SetRelativeLocation(FVector(0,0,-80));

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(swordMeshComp);
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox->SetRelativeLocation(FVector(0.0f, 0.0f, -135.0f));
	HitBox->SetBoxExtent(FVector(15.0f, 2.0f, 105.0f));
}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASword::WeaponHit);

	skillDamagePercents.Init(1, 3);
	//swordHitSound.Init(nullptr, 3);
}

void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASword::SwordBasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("SwordBasicAttack"));
}

void ASword::SwordSkill1()
{
	// SkillStruct의 스킬 정보를 가져와서 
	// 스킬포인트 값에 따라 공격력, 방어력 값을 다르게 넣어주면 됨

	UE_LOG(LogTemp, Warning, TEXT("SwordSkill1"));
}

void ASword::SwordSkill2()
{
	UE_LOG(LogTemp, Warning, TEXT("SwordSkill2"));
}

void ASword::SwordSkill3()
{
	UE_LOG(LogTemp, Warning, TEXT("SwordSkill3"));
}

void ASword::StartSwordTrace(int32 _currentSkillNum)
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	/*
	if (enemies.Num() > 0) {
		enemies.Empty();
	}
	*/
	
	// 0 : 기본, 1 : 스킬1, 2 : 스킬2, 3 : 스킬3
	currentSkillNum = _currentSkillNum;

	//UGameplayStatics::PlaySound2D(GetWorld(), swordSkill1Sound);
	/*
	GetWorldTimerManager().SetTimer(traceHdl, [&] {
		LoopSwordTrace();
	}, 0.001, true);
	*/
}

void ASword::LoopSwordTrace()
{
	//ServerRPC_ApplyDamage();
}

void ASword::StopSwordTrace()
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetWorldTimerManager().ClearTimer(traceHdl);
}

void ASword::ServerRPC_ApplyDamage_Implementation(ABaseEnemy* _enemyREF)
{
	/*
	TArray<FHitResult> hitsArr;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->SweepMultiByChannel(hitsArr, traceStart->GetComponentLocation(), traceEnd->GetComponentLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(30.0f), params);

	//DrawDebugCapsule(GetWorld(), traceEnd->GetComponentLocation(), 100, 30, GetActorRotation().Quaternion(), FColor::Red, false, 1, 0, 1);

	for (int i = 0; i < hitsArr.Num(); i++)
	{

		if (hitsArr[i].GetActor()->ActorHasTag("Enemy"))
		{
			if (!enemies.Contains(hitsArr[i].GetActor()))
			{
				enemies.Add(hitsArr[i].GetActor());

				float damage = 0;

				int32 randomIndex = FMath::RandRange(0, 2);

				//UE_LOG(LogTemp, Warning, TEXT("%d"), randomIndex);

				if (gi) {
					switch (currentSkillNum)
					{
						// 검 기본 공격
					case 0:
						damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("SwordBasic", ""))->DamagePower + (weaponAttackPower * basicAttackDamagePercent * gi->buffSwordDamagePercent);
						UGameplayStatics::PlaySound2D(GetWorld(), swordHitSound[randomIndex]);
						UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
						break;
						// 검 스킬1
					case 1:
						damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword1", ""))->DamagePower + (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 0
						UGameplayStatics::PlaySound2D(GetWorld(), sword1HitSound);
						UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
						break;
						// 검 스킬2
					case 2:
						damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword2", ""))->DamagePower * (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 1
						UGameplayStatics::PlaySound2D(GetWorld(), sword2HitSound);
						UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
						break;
						// 검 스킬3
					case 3:
						damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword3", ""))->DamagePower * (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 2
						UGameplayStatics::PlaySound2D(GetWorld(), sword3HitSound);
						UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
						break;
					default:
						break;
					}
					gi->swordDamage = damage;
				}


				UGameplayStatics::ApplyDamage(hitsArr[i].GetActor(), damage, nullptr, nullptr, nullptr);

				MultiRPC_ApplyDamage(hitsArr[i].GetActor()->GetActorLocation());
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Not Enemy"));
		}
	}
	*/
	MultiRPC_ApplyDamage(_enemyREF->GetActorLocation());
}

void ASword::MultiRPC_ApplyDamage_Implementation(FVector hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, hitLoc);
}

void ASword::WeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseEnemy* enemyREF = Cast<ABaseEnemy>(OtherActor);
	if (enemyREF)
	{
		float damage = 0;

		int32 randomIndex = FMath::RandRange(0, 2);

		//UE_LOG(LogTemp, Warning, TEXT("%d"), randomIndex);

		if (gi) {
			switch (currentSkillNum)
			{
				// 검 기본 공격
			case 0:
				damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("SwordBasic", ""))->DamagePower + (weaponAttackPower * basicAttackDamagePercent * gi->buffSwordDamagePercent);
				UGameplayStatics::PlaySound2D(GetWorld(), swordHitSound[randomIndex]);
				UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
				break;
				// 검 스킬1
			case 1:
				damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword1", ""))->DamagePower + (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 0
				UGameplayStatics::PlaySound2D(GetWorld(), sword1HitSound);
				UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
				break;
				// 검 스킬2
			case 2:
				damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword2", ""))->DamagePower * (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 1
				UGameplayStatics::PlaySound2D(GetWorld(), sword2HitSound);
				UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
				break;
				// 검 스킬3
			case 3:
				damage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Sword3", ""))->DamagePower * (weaponAttackPower * skillDamagePercents[currentSkillNum - 1] * gi->buffSwordDamagePercent);	// 2
				UGameplayStatics::PlaySound2D(GetWorld(), sword3HitSound);
				UE_LOG(LogTemp, Warning, TEXT("weaponAttackPower : %d"), weaponAttackPower);
				break;
			default:
				break;
			}
			gi->swordDamage = damage;
			float atkResult = UGameplayStatics::ApplyDamage(enemyREF, damage, nullptr, this, damageType);
			UE_LOG(LogTemp, Warning, TEXT("Player HIT!"));
		}
		ServerRPC_ApplyDamage(enemyREF);
	}

}

void ASword::CheckBasicAttackCnt(int32 _swordBasicAttackCnt)
{
	swordBasicAttackCnt = _swordBasicAttackCnt;

	switch (swordBasicAttackCnt)
	{
	// 제일 마지막 공격
	case 0:
		basicAttackDamagePercent = 1.6f;
		break;
	case 1:
		basicAttackDamagePercent = 1.0f;
		break;
	case 2:
		basicAttackDamagePercent = 1.0f;
		break;
	case 3:
		basicAttackDamagePercent = 1.2f;
		break;
	case 4:
		basicAttackDamagePercent = 1.2f;
		break;
	default:
		break;
	}
}

void ASword::UpgradeSwordEffect(int32 weaponLevel)
{
	ServerRPC_ShowEffect(weaponLevel);

}

void ASword::ServerRPC_ShowEffect_Implementation(int32 NewUpgradeValue)
{
	if (NewUpgradeValue <= 1)
	{
		EffectSwordScale = FVector(0, 0, 0);
	}
	else if (NewUpgradeValue <= 10)
	{
		EffectSwordScale = FVector(0.3, 0.3, 0.3);
	}
	else if (NewUpgradeValue <= 19)
	{
		EffectSwordScale = FVector(0.6, 0.6, 0.6);
	}
	else
	{
		EffectSwordScale = FVector(1.0, 1.0, 1.0);
	}

	OnRap_ShowEffect();
}


void ASword::OnRap_ShowEffect()
{
	WeaponEffect->SetWorldScale3D(EffectSwordScale);
}

void ASword::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 에너미 체력 동기화
	DOREPLIFETIME(ASword, EffectSwordScale);
}

