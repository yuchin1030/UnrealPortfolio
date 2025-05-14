// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonEditCharacterController.h"
#include "Yohan/DungeonEditCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>

void ADungeonEditCharacterController::BeginPlay()
{
	Super::BeginPlay();

    SetInputMode(FInputModeGameOnly());
}

void ADungeonEditCharacterController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn)
    {
        InPawn->EnableInput(this);
    }
}


