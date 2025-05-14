// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BGMActor.h"
#include "Components/AudioComponent.h"
#include "OurGameModeBase.h"
#include "GJY/CustomModeBase.h"
#include "Yohan/DungeonEditGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Yohan/DungeonEditCharacter.h"
#include "Yohan/DungeonEditComponent.h"
#include "Yohan/OurGameStateBase.h"
#include "OurGameInstance.h"

// Sets default values
ABGMActor::ABGMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	audioComp->SetupAttachment(rootComp);
	audioComp->bAutoActivate = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABGMActor::BeginPlay()
{
	Super::BeginPlay();

	OGM = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
	CGM = Cast<ACustomModeBase>(GetWorld()->GetAuthGameMode());
	DGM = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode());
	GI = Cast<UOurGameInstance>(GetGameInstance());
	OGS = Cast<AOurGameStateBase>(GetWorld()->GetGameState());

	UE_LOG(LogTemp, Warning, TEXT("BGM Begin"));
	/*
	if (HasAuthority()) {
		if (OGM) {
			OGM->loadingEndDelegate.BindUFunction(this, FName("PlayBGM"));
			UE_LOG(LogTemp, Warning, TEXT("OGM Play Sound!"));
		}

		if (CGM) {
			CGM->loadingEndDelegate.BindUFunction(this, FName("PlayBGM"));
			UE_LOG(LogTemp, Warning, TEXT("CGM Play Sound!"));
		}

		if (DGM) {
			ADungeonEditCharacter* DEC = Cast<ADungeonEditCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			if (DEC)
			{
				UDungeonEditComponent* DECC = DEC->FindComponentByClass<UDungeonEditComponent>();
				if (DECC)
				{
					DECC->loadingEndDelegate.BindUFunction(this, FName("PlayBGM"));
					UE_LOG(LogTemp, Warning, TEXT("DECC Play Sound!"));
				}
			}
		}

		if (GI) {
			GI->loadingEndDelegate.BindUFunction(this, FName("PlayBGM"));
			UE_LOG(LogTemp, Warning, TEXT("GI Play Sound!"));
		}

		if (OGS) {
			OGS->loadingEndDelegate.BindUFunction(this, FName("PlayBGM"));
			UE_LOG(LogTemp, Warning, TEXT("OGS Play Sound!"));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("No Host?"));
	}*/
	FTimerHandle playTimer;
	GetWorld()->GetTimerManager().SetTimer(playTimer, ([&](){
		PlayBGM();
	}), 5.0f, false);
}

// Called every frame
void ABGMActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABGMActor::PlayBGM()
{
	if (!bIsPlayStart)
	{
		bIsPlayStart = true;
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_PlayBGM();
		UE_LOG(LogTemp, Warning, TEXT("BGM Start"));
	}
}

void ABGMActor::ServerRPC_PlayBGM_Implementation()
{
	MultiRPC_PlayBGM();
}

void ABGMActor::MultiRPC_PlayBGM_Implementation()
{
	audioComp->Play();
}


void ABGMActor::StopBGM()
{
	audioComp->Stop();
}

