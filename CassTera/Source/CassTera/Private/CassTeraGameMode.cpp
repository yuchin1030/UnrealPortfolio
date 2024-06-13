// Copyright Epic Games, Inc. All Rights Reserved.

#include "CassTeraGameMode.h"
#include "CassTeraCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LobbyWidget.h"

ACassTeraGameMode::ACassTeraGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	bActorSeamlessTraveled = false;
}

void ACassTeraGameMode::StartPlay()
{
	Super::StartPlay();

	// LobbyWidget_BP �� �ִٸ�
	if (LobbyWidget_BP)
	{
		// LobbyWidget UI�� �����
		auto lobbyUI = Cast<ULobbyWidget>(CreateWidget<ULobbyWidget>(GetWorld(), LobbyWidget_BP));

		if (lobbyUI)
		{	
			// lobbyUI�� ����Ʈ�� ����
			lobbyUI->AddToViewport();

			auto* pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (pc)
			{
				pc->SetShowMouseCursor(true);
			}
		}
	}
}
