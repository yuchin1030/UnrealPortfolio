// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonPlayerController.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/GameModeBase.h>
#include <../../../../../../../Source/Runtime/Engine/Public/Net/UnrealNetwork.h>
#include "HidePlayer.h"
#include "HidePlayerCamera.h"
#include "CassTeraCharacter.h"
#include "GameTimerWidget.h"
#include "MainUI.h"
#include "EngineUtils.h"
#include "PersonPlayerGameModeBase.h"
#include "CassteraGameState.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "HideAndSeekGameInstance.h"

APersonPlayerController::APersonPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// �� �ʱ�ȭ
	SeakPlayerPawn = nullptr;
	HidePlayerPawn = nullptr;


	// �� Ŭ������ �����Ǿ����� Ȯ��
	bReplicates = true;
}


// void APersonPlayerController::ServerRPC_CreateTimerUI_Implementation()
// {
// 	MultiRPC_CreateTimerUI();
// }
// 
// void APersonPlayerController::MultiRPC_CreateTimerUI_Implementation()
// {
// 	gameTimerwidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(),WBP_gameTimerWidget));
// }

void APersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	////ServerRPC_DefinePawnClass();
	//int32 number = FMath::RandRange(0, 100);
	//if (rate < number)
	//{
	//	ServerRPC_SetPawn(SeakPlayerPawn);

	//}
	//else
	//{
	//	ServerRPC_SetPawn(HidePlayerPawn);
	//}
	///*if (IsLocalController()) 
	//{

	//}*/
//	if (HasAuthority())
//	{

	//	}

	if (IsLocalController())
	{
		mainUI = Cast<UMainUI>(CreateWidget(GetWorld(), WBP_MainUI));
		UE_LOG(LogTemp, Error, TEXT("Create MainUI"));
	}
}

void APersonPlayerController::OnPossess(APawn* aPawn)
{
	//gameTimerwidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(), WBP_gameTimerWidget));
	//mainUI = Cast<UMainUI>(CreateWidget(GetWorld(), WBP_MainUI));

	Super::OnPossess(aPawn);

	gm = Cast<APersonPlayerGameModeBase>(GetWorld()->GetAuthGameMode());

	//gameTimerwidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(), WBP_gameTimerWidget));

	

	gs = Cast<ACassteraGameState>(UGameplayStatics::GetGameState(GetWorld()));

		if (auto* p = Cast<AHidePlayer>(GetPawn()))
		{
			gm->hidePlayers.Add(p);
			gs->hidePlayerCount = gm->hidePlayers.Num();
// 			_hidePlayerCount = gs->hidePlayerCount;
			gs->ServerRPC_HidePlayerCount();
			UE_LOG(LogTemp, Error, TEXT("Rest HidePlayer Count : %d"), gs->hidePlayerCount);

		}	
	
}

void APersonPlayerController::Tick(float DeltaTime)
{
	if (gs)
	{
		if (HasAuthority() && IsLocalController())
		{
			gs->ServerRPC_CalculateTime();

		}
		
	}
} 



void APersonPlayerController::ServerRPC_DefinePawnClass_Implementation()
{
	//MultiRPC_DefinePawnClass();
}

void APersonPlayerController::MultiRPC_DefinePawnClass_Implementation()
{
	if (IsLocalController())
	{
		////�ؽ�Ʈ ������ ���ڿ� �迭�� �ε�
		//TArray<FString> TextStrings;
		//const FString FilePath = FPaths::ProjectContentDir() + "Textfiles/PlayerSettings.txt";
		//FFileHelper::LoadFileToStringArray(TextStrings, *FilePath);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *FilePath);

		int32 number = FMath::RandRange(0, 100);
		if (rate < number)
		{
			ServerRPC_SetPawn(SeakPlayerPawn);
		}
		else
		{
			ServerRPC_SetPawn(HidePlayerPawn);
		}
	}
}

void APersonPlayerController::ServerRPC_SetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
{
	/*APawn* prevPawn = GetPawn();

	UnPossess();*/

	MyPawnClass = InPawnClass;

	//AActor* spt = GetWorld()->GetAuthGameMode()->FindPlayerStart(this);
	//FActorSpawnParameters params;
	//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//
	//auto* newPawn = GetWorld()->SpawnActor<APawn>(MyPawnClass, spt->GetActorTransform(), params);
	//Possess(newPawn);
	//
	/*
	if (prevPawn)
		prevPawn->Destroy();*/

		//�ð� ���� ������ PawnClass�� �������� ���� ��츦 ����Ѵ�
	UE_LOG(LogTemp, Warning, TEXT("%s"), MyPawnClass);
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);

}

bool APersonPlayerController::ServerRPC_SetPawn_Validate(TSubclassOf<APawn> InPawnClass)
{
	return true;
}

void APersonPlayerController::ServerRPC_ChangeToSpectator_Implementation(AHidePlayer* hidePlayer, bool isOldPawnDestroy = false)
{
	origin = Cast<AHidePlayer>(hidePlayer);
	if (bHidePlayerDie == true)
	{
		return;
	}

	if (origin != nullptr)
	{
		if (origin->bDie == true)
		{
			bHidePlayerDie = true;
		}

		UE_LOG(LogTemp, Warning, TEXT("null"));
		//MultiRPC_ChangeToSpectator(origin);
		UnPossess();
		FVector loc = origin->GetActorLocation() + FVector(0, 50, 50);
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		watchingCam = GetWorld()->SpawnActor<AHidePlayerCamera>(watcingCam_bp, loc, FRotator::ZeroRotator, params);
		spectator = Cast<AHidePlayerCamera>(watchingCam);

		if (spectator != nullptr)
		{
			Possess(spectator);
		}

		if (isOldPawnDestroy)
		{
			hidePlayer->Destroy();
		}

	}
	//ClientRPC_ChangeToSpectator(origin);

}
// �ϴ� �Ⱦ�
void APersonPlayerController::ClientRPC_ChangeToSpectator_Implementation(AHidePlayer* hidePlayer)
{
	//origin = hidePlayer;
	//// 

	//UnPossess();
	//FVector loc = hidePlayer->GetActorLocation() + FVector(0, 50, 50);
	//FActorSpawnParameters params;
	//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//watchingCam = GetWorld()->SpawnActor<AHidePlayerCamera>(watcingCam_bp, loc, FRotator::ZeroRotator, params);
	//spectator = Cast<AHidePlayerCamera>(watchingCam);

	//if (spectator != nullptr)
	//{
	//	Possess(spectator);
	//}
}

void APersonPlayerController::ServerRPC_ChangeToPlayer_Implementation()
{
	if (bHidePlayerDie == true)
	{
		return;
	}
	auto* hidePlayer = origin;
	if (hidePlayer->Controller == nullptr)
	{
		Possess(hidePlayer);
	}
}

void APersonPlayerController::ChangeToPlayer()
{
	ServerRPC_ChangeToPlayer();
}

void  APersonPlayerController::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps)  const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//s
	DOREPLIFETIME(APersonPlayerController, MyPawnClass);

}