// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/MoveToDungeonNPC.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include "ChallengersCharacter.h"
#include "Yohan/MoveToDungeonWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/PrimitiveComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"

AMoveToDungeonNPC::AMoveToDungeonNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	nPCArea = CreateDefaultSubobject<UBoxComponent>(TEXT("NPC Area"));
	SetRootComponent(nPCArea);
	

	nPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NPC"));
	nPC->SetupAttachment(RootComponent);

	
	
}

void AMoveToDungeonNPC::BeginPlay()
{
	Super::BeginPlay();
	
	nPCArea->OnComponentBeginOverlap.AddDynamic(this, &AMoveToDungeonNPC::OnOverlapBegin);
}

void AMoveToDungeonNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto temp = Cast<AChallengersCharacter>(OtherActor);
	// 만약 오버랩 된 대상이 플레이어 이고, 던전 이동 UI가 있다면..
	if (temp && moveToDungeonUI_BP && HasAuthority())
	{
		// 던전 이동 UI를 띄운다
		moveToDungeonUI = CreateWidget<UMoveToDungeonWidget>(GetWorld(), moveToDungeonUI_BP);

		moveToDungeonUI->AddToViewport();
		player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
				
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Move To DungeonNPC None"));
	}
	
}

void AMoveToDungeonNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

