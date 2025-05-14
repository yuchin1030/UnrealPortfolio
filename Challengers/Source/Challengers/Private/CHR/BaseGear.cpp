// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseGear.h"
#include "OurGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ABaseGear::ABaseGear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	gearEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	gearEffectComp->SetupAttachment(rootComp);
	gearEffectComp->bAutoActivate = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseGear::BeginPlay()
{
	Super::BeginPlay();
	
	SetOwner(GetWorld()->GetFirstPlayerController());

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
}

// Called every frame
void ABaseGear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (activeTime < gearStat.activeTime)
	{
		activeTime+=DeltaTime;
	}
	else {
		gearEffectComp->Deactivate();
		if (enemyREF) {
			enemyREF->GetMesh()->SetOverlayMaterial(nullptr);
		}
	}
}

/*
	bool bIsBuffType;//true�� �ڱⰭȭ��, false�� �߻���
	float useCooldown;//���� ���� ���ð�
	float activeTime;//�ߵ� �� ���� �ð�
	TSubclassOf<class ABaseGear> shape;//��� ��ü�� �������Ʈ
	TSubclassOf<class AActor> shootActor;//�߻��� �ߵ��� �߻�Ǵ� �߻�ü
	class UNiagaraSystem* gearActiveEffect;//�ߵ�����Ʈ
	class UMaterialInstance* overlayMat;//���ӽð����� ���̴� ��������

	int32 weight;//���� ����
	int32 cost;//������ ����
	FString name;//��ü�� �̸�
	FString discription;//��ü�� ����
*/

void ABaseGear::DataInit(FName _rowName, bool bIsWeapon1, ABaseEnemy* ownedEnemy)
{
	enemyREF = ownedEnemy;
	rowName = _rowName;
	if (gi) {
		gearStat = *(gi->DT_GearData->FindRow<FgearSpec>(rowName, ""));
		gearNum = FCString::Atoi(*rowName.ToString());
		gearEffectComp->SetAsset(gearStat.gearActiveEffect);
		if (gearStat.gearActiveEffect != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Buff!"));
			gearEffectComp->Activate(true);
			FTimerHandle lodingActive;
			GetWorld()->GetTimerManager().SetTimer(lodingActive, FTimerDelegate::CreateLambda([&]() {
				gearEffectComp->Deactivate();
			}), 1.0f, false);
		}
		activeTime = gearStat.activeTime;
	}
}

void ABaseGear::ActivateGear()
{
	/*FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FRotator shootRot = enemyREF->GetActorForwardVector().Rotation();

	switch (gearNum)
	{
	case 0:
		gearEffectComp->Activate(true);
		enemyREF->GetMesh()->SetOverlayMaterial(gearStat.overlayMat);
		activeTime = 0.0f;
	break;
	case 1:
		for (int i = 0; i < 8; i++)
		{
			AActor* shootREF = GetWorld()->SpawnActor<AActor>(gearStat.shootActor, enemyREF->GetActorLocation(), shootRot, params);
			shootREF->SetActorLocation(shootREF->GetActorLocation() + shootREF->GetActorForwardVector() * 150);
			shootRot.Yaw += 45.0f;
		}
	default:
		break;
	}*/
}

