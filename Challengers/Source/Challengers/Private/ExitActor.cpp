// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitActor.h"
#include "Components/BoxComponent.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "OurGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystemUtils.h"

// Sets default values
AExitActor::AExitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AExitActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AExitActor::EXIT);
}

// Called every frame
//void AExitActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

void AExitActor::EXIT(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AChallengersCharacter* playerREF = Cast<AChallengersCharacter>(OtherActor);
	if (playerREF) {
		if (HasAuthority()) {
			UE_LOG(LogTemp, Warning, TEXT("Exit Host"));
			AMainPlayerController* pc = Cast<AMainPlayerController>(playerREF->Controller);
			pc->ClientReturnToMainMenuWithTextReason(NSLOCTEXT("HostOutMsg", "HostOut", "Host Exited!"));
			auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
			if (gi) {
				bool result = gi->sessionInterface->DestroySession(FName(*gi->mySessionName));
			}
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("SingleMap"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Exit Client"));

			auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
			if (gi)
			{
				bool result = gi->sessionInterface->DestroySession(FName(*gi->mySessionName));

				if (result)
				{
					auto* pc = GetWorld()->GetFirstPlayerController();
					pc->ClientTravel("/Game/Gothic_Cathedral/Maps/SingleMap", ETravelType::TRAVEL_Absolute);
				}
			}
		}
	}
}
