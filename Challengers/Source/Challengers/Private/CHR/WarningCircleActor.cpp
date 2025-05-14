// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/WarningCircleActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AWarningCircleActor::AWarningCircleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	outCircle = CreateDefaultSubobject<UDecalComponent>(TEXT("OutLine"));
	outCircle->SetupAttachment(rootComp);
	outCircle->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	outCircle->DecalSize = FVector(10.0f, 150.0f, 150.0f);
	outCircle->SetVisibility(false);

	inCircle = CreateDefaultSubobject<UDecalComponent>(TEXT("InCircle"));
	inCircle->SetupAttachment(rootComp);
	inCircle->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	inCircle->SetRelativeScale3D(FVector(1.0f, 0.1f, 0.1f));
	inCircle->DecalSize = FVector(10.0f, 150.0f, 150.0f);
	inCircle->SetVisibility(false);

	playingCasting = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopSound"));
	playingCasting->SetupAttachment(rootComp);
	playingCasting->bAutoActivate = false;
}

// Called when the game starts or when spawned
//void AWarningCircleActor::BeginPlay()
//{
//	Super::BeginPlay();
//}

// Called every frame
void AWarningCircleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsStart)
	{
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_SizeChange();
	}
}

//데칼 초기화. InputSize는 Scale값이므로 1이 기본.
void AWarningCircleActor::Init(FVector InputSize, float InputLifeTime)
{
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_Init(InputSize, InputLifeTime);
}

void AWarningCircleActor::ServerRPC_Init_Implementation(FVector _InputSize, float _InputLifeTime)
{
	lifeTime = _InputLifeTime;
	warningSoundTime = lifeTime - 0.5f;
	targetSize = _InputSize;
}

void AWarningCircleActor::ServerRPC_SizeChange_Implementation()
{
	lerpTime = FMath::Min(lerpTime + GetWorld()->GetDeltaSeconds(), lifeTime);

	size = FMath::Lerp(FVector(1.0f, 0.1f, 0.1f), targetSize, lerpTime / lifeTime);
	OnRep_SizeChange();

	if (lerpTime == lifeTime)
	{
		WarningDeactivate();
	}
}

void AWarningCircleActor::OnRep_SizeChange()
{
	inCircle->SetRelativeScale3D(size);

	if (lerpTime >= warningSoundTime)
	{
		if (playingCasting)
		{
			playingCasting->SetVolumeMultiplier(FMath::Lerp(1.0f, 0.0f, (lerpTime - warningSoundTime) / 0.5f));
		}
	}
}

void AWarningCircleActor::WarningActivate(FVector fireLoc)
{
	ServerRPC_Activate(fireLoc);
}

void AWarningCircleActor::ServerRPC_Activate_Implementation(FVector fireLoc)
{
	bIsStart = true;
	SetActorLocation(fireLoc);
	OnRep_ShowCircle();
}

void AWarningCircleActor::OnRep_ShowCircle()
{
	if (bIsStart) {
		outCircle->SetVisibility(true);
		inCircle->SetVisibility(true);
		if (playingCasting)
		{
			playingCasting->SetVolumeMultiplier(1.0f);
			playingCasting->Play();
		}
	}
	else {
		outCircle->SetVisibility(false);
		inCircle->SetVisibility(false);
		if (playingCasting)
		{
			playingCasting->Stop();
		}
	}
}

void AWarningCircleActor::WarningDeactivate()
{
	ServerRPC_Deactivate();
}

void AWarningCircleActor::ServerRPC_Deactivate_Implementation()
{
	bIsStart = false;
	OnRep_ShowCircle();
	lerpTime = 0.0f;
	if (IsInGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("main thread"));
	}
	else{
		AsyncTask(ENamedThreads::GameThread, [this](){
			UE_LOG(LogTemp, Warning, TEXT("AsyncTask -> main thread"));
		});
	}

	if (warningTimeEndDelegate.IsBound()) {
		warningTimeEndDelegate.Execute();
	}
}

void AWarningCircleActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 경고원 크기 동기화
	DOREPLIFETIME(AWarningCircleActor, size);
	DOREPLIFETIME(AWarningCircleActor, bIsStart);
	DOREPLIFETIME(AWarningCircleActor, lerpTime);
}