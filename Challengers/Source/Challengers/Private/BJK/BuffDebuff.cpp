#include "BJK/BuffDebuff.h"
#include "ChallengersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Sword.h"
#include "SkillStruct.h"
#include "OurGameInstance.h"

ABuffDebuff::ABuffDebuff()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABuffDebuff::BeginPlay()
{
	Super::BeginPlay();

   
	
}


void ABuffDebuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

