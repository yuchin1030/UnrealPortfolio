#include "BJK/UpgradeWeaponNPC.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "BJK/MainPlayerWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


AUpgradeWeaponNPC::AUpgradeWeaponNPC()
{
 	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(RootComponent);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AUpgradeWeaponNPC::OnOverlapBegin);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AUpgradeWeaponNPC::OnOverlapEnd);

}


void AUpgradeWeaponNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AChallengersCharacter* Player = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Visible);
	}

	if (Player)
	{
		Player->bShowWeaponUpgradeNPC = false;


	}

}

void AUpgradeWeaponNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AChallengersCharacter* Player = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Player)
	{
		Player->bShowWeaponUpgradeNPC = true;
	}
}
