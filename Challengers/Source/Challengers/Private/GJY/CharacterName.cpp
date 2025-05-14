// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/CharacterName.h"
#include "Components/TextBlock.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>



void UCharacterName::NativeConstruct()
{
	for (TActorIterator<AChallengersCharacter> it(GetWorld()); it; ++it)
	{
		CC = *it;
	}
	FString NickName = CC->playerName;
	ShowNickName(NickName);

	UE_LOG(LogTemp, Warning , TEXT("LOADNAME : %s"), *NickName);
}

void UCharacterName::ShowNickName(FString PlayerNickName)
{

	if(CC!=nullptr)
	{ 
		Text_Name -> SetText(FText::FromString(PlayerNickName));
		UE_LOG(LogTemp, Warning, TEXT("Player Name Load Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CC is nullptr"));
	}

}

