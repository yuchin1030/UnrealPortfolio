

#include "CustomNPC.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "BJK/MainPlayerWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>



ACustomNPC::ACustomNPC()
{

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(RootComponent);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACustomNPC::OnOverlapBegin);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &ACustomNPC::OnOverlapEnd);

	

}


void ACustomNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AChallengersCharacter>(OtherActor);
	auto temp = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Visible);
	if (temp)
	{
		temp->bShowSelectCustomNPC = false;

	
	}

}

void ACustomNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Player = Cast<AChallengersCharacter>(OtherActor);
	auto temp = Cast<AChallengersCharacter>(OtherActor);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->mainplayerWidget->Image_Interaction->SetVisibility(ESlateVisibility::Hidden);
	if (temp)
	{
		temp->bShowSelectCustomNPC = true;
	}
}


