// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomEnemySetter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "BJK/MainPlayerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATestRoomEnemySetter::ATestRoomEnemySetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	boxComp->SetupAttachment(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(rootComp);

	floatingNameComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameComp"));
	floatingNameComp->SetupAttachment(rootComp);
	floatingNameComp->SetWidgetSpace(EWidgetSpace::World);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ATestRoomEnemySetter::OnOverlapBegin);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &ATestRoomEnemySetter::OnOverlapEnd);
}

// Called when the game starts or when spawned
//void ATestRoomEnemySetter::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ATestRoomEnemySetter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ATestRoomEnemySetter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AChallengersCharacter* Player = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Visible);
	}

	if (Player)
	{
		Player->bShowEnemySetting = false;
	}
}

void ATestRoomEnemySetter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AChallengersCharacter* Player = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Player)
	{
		Player->bShowEnemySetting = true;
	}
}

