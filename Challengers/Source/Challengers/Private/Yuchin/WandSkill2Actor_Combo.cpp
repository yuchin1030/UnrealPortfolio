// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/WandSkill2Actor_Combo.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "OurGameInstance.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SkillStruct.h"
#include "../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "../../../FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"

AWandSkill2Actor_Combo::AWandSkill2Actor_Combo()
{
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	fxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("fxComp"));
	fxComp->SetupAttachment(defaultSceneRoot);
	fxComp->SetRelativeLocation(FVector(0, 0, -90));

	box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("box1"));
	box2 = CreateDefaultSubobject<UBoxComponent>(TEXT("box2"));
	box3 = CreateDefaultSubobject<UBoxComponent>(TEXT("box3"));
	box4 = CreateDefaultSubobject<UBoxComponent>(TEXT("box4"));
	box5 = CreateDefaultSubobject<UBoxComponent>(TEXT("box5"));
	box6 = CreateDefaultSubobject<UBoxComponent>(TEXT("box6"));

	box1->SetupAttachment(defaultSceneRoot);
	box1->SetRelativeLocation(FVector(-2.846097, -616.506352, 0));
	box1->SetBoxExtent(FVector(111.773825, 571.366935, 32));

	box2->SetupAttachment(defaultSceneRoot);
	box2->SetRelativeLocation(FVector(555.0, -315.770866, 0));
	box2->SetRelativeRotation(FRotator(0, 60, 0));
	box2->SetBoxExtent(FVector(111.773825, 571.366935, 32));

	box3->SetupAttachment(defaultSceneRoot);
	box3->SetRelativeLocation(FVector(552.052014, 314.201602, 0));
	box3->SetRelativeRotation(FRotator(0, 120, 0));
	box3->SetBoxExtent(FVector(111.773825, 571.366935, 32));

	box4->SetupAttachment(defaultSceneRoot);
	box4->SetRelativeLocation(FVector(2.153899, 640.666421, 0));
	box4->SetBoxExtent(FVector(111.773825, 571.366935, 32));

	box5->SetupAttachment(defaultSceneRoot);
	box5->SetRelativeLocation(FVector(-568.901962, 328.485395, 0));
	box5->SetRelativeRotation(FRotator(0, 60, 0));
	box5->SetBoxExtent(FVector(111.773825, 571.366935, 32));

	box6->SetupAttachment(defaultSceneRoot);
	box6->SetRelativeLocation(FVector(-552.412126, -329.80418, 0));
	box6->SetRelativeRotation(FRotator(0, 120, 0));
	box6->SetBoxExtent(FVector(111.773825, 571.366935, 32));

}

void AWandSkill2Actor_Combo::BeginPlay()
{
	Super::BeginPlay();
	
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	FTimerHandle destroyHdl;
	GetWorldTimerManager().SetTimer(destroyHdl, [&] {
		Destroy();
	}, 2.5f, false);

	this->OnActorBeginOverlap.AddDynamic(this, &AWandSkill2Actor_Combo::WandSkill2ComboHit);
}

void AWandSkill2Actor_Combo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWandSkill2Actor_Combo::WandSkill2ComboHit(AActor* OverlappedActor, AActor* OtherActor)
{

	if (OtherActor->ActorHasTag("Enemy"))
	{
		gi->wandDamage = (gi->DT_SkillInfo->FindRow<FSkillsInfo>("Magic2", ""))->DamagePower * damagePercent * gi->buffWandDamagePercent;
		UGameplayStatics::ApplyDamage(OtherActor, gi->wandDamage, nullptr, nullptr, nullptr);

		ServerRPC_WandSkill2ComboHit(OtherActor->GetActorLocation());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("WandSkill2Combo : Not Enemy"));
	}
}

void AWandSkill2Actor_Combo::ServerRPC_WandSkill2ComboHit_Implementation(FVector hitLoc)
{
	MultiRPC_WandSkill2ComboHit(hitLoc);
}

void AWandSkill2Actor_Combo::MultiRPC_WandSkill2ComboHit_Implementation(FVector _hitLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitVFX, _hitLoc);
}

