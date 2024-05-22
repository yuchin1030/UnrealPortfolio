

#include "Toast.h"
#include "ChinToastRecipe.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>

AToast::AToast()
{
	PrimaryActorTick.bCanEverTick = true;

	makingArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Making Area"));
	makingArea->SetupAttachment(RootComponent);
	makingArea->SetBoxExtent(FVector(10));

	pickUpArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Pick Up Area"));
	pickUpArea->SetupAttachment(RootComponent);
	pickUpArea->SetBoxExtent(FVector(10,10,1));
	pickUpArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AToast::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AChinToastRecipe> toast(GetWorld()); toast; ++toast)
	{
		recipe = *toast;
	}
	
}

void AToast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

