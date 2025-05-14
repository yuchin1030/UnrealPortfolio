// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChallengersGameMode.h"
#include "ChallengersCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChallengersGameMode::AChallengersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
