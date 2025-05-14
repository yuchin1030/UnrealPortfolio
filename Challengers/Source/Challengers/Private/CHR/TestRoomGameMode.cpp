// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomGameMode.h"
#include "EngineUtils.h"
#include "Engine/TargetPoint.h"
#include "ChallengersCharacter.h"
#include "CHR/DrawRangeActor.h"
#include "CHR/TestRoomAIWidget.h"
#include "CHR/TestRoomSetWidget.h"
#include "CHR/TestRoomSaveWidget.h"
#include "CHR/TestRoomLoadWidget.h"
#include "BJK/MainPlayerWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "MainPlayerController.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include "LoadingWidget.h"
#include "Components/Image.h"

#define MAXHP 1000
#define MAXMP 1000

ATestRoomGameMode::ATestRoomGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestRoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	AMainPlayerController* pc = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	if (loadingUI_BP)
	{
		loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);
		if (loadingUI)
		{
			loadingUI->AddToViewport(1);
			loadingUI->HideAll();
			loadingUI->Image_Test->SetVisibility(ESlateVisibility::Visible);
			loadingUI->FadeOutStart(2);
			FTimerHandle loadingTimer;
			GetWorld()->GetTimerManager().SetTimer(loadingTimer, ([&](){
				loadingUI->SetVisibility(ESlateVisibility::Hidden);
				loadingUI->RemoveFromParent();
			}), 3.0f, false);
		}
	}

	for (TActorIterator<ATargetPoint> iter(GetWorld()); iter; ++iter) {
		spawnPoint = *iter;
	}
	for (TActorIterator<ADrawRangeActor> iter(GetWorld()); iter; ++iter) {
		rangeActor = *iter;
	}
	AIData.battleDist = 100.0f;
	AIData.playerFindDist = 2000.0f;
	AIData.targetChangeRate = 1.0f;
	AIData.phase2Rate = 0.8f;
	AIData.phase3Rate = 0.6f;
	SpawnEnemy();

	pc->SetInputMode(FInputModeGameOnly());
}

void ATestRoomGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerREF){
		if (playerREF->HP < MAXHP / 2)
		{
			playerREF->HP = MAXHP / 2;
		}

		if (playerREF->MP < MAXMP)
		{
			playerREF->MP = MAXMP;
		}
	}
	else{
		for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
			playerREF = *iter;
		}
	}

	if (enemyREF)
	{
		if (enemyREF->currentHP <= 0)
		{
			enemyREF = nullptr;
			if (rangeActor)
			{
				rangeActor->enemyREF = nullptr;
			}
		}

		if (bIsRotate) {
			if (bIsBack) {
				enemyREF->SetActorRotation(FRotator(0.0f, FMath::InterpEaseOut(180.0f, 0.0f, GetWorld()->GetTimerManager().GetTimerElapsed(rotateTimer) / 0.5f, 2.0f), 0.0f));
			}
			else {
				enemyREF->SetActorRotation(FRotator(0.0f, FMath::InterpEaseOut(0.0f, 180.0f, GetWorld()->GetTimerManager().GetTimerElapsed(rotateTimer) / 0.5f, 2.0f), 0.0f));
			}
		}
	}

}

void ATestRoomGameMode::RotateEnemy(bool _bIsBack)
{
	bIsRotate = true;
	bIsBack = _bIsBack;
	if (!_bIsBack) {
		GetWorld()->GetTimerManager().SetTimer(rotateTimer, FTimerDelegate::CreateLambda([&]() {
			enemyREF->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
			bIsRotate = false;
			}), 0.5f, false);
	}
	else {
		GetWorld()->GetTimerManager().SetTimer(rotateTimer, FTimerDelegate::CreateLambda([&]() {
			enemyREF->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
			bIsRotate = false;
			}), 0.5f, false);
	}
}

void ATestRoomGameMode::DestroyEnemy()
{
	if (enemyREF)
	{
		enemyREF->Died(false);
		enemyREF = nullptr;
	}
}

void ATestRoomGameMode::SpawnEnemy()
{
	//스폰하기 전 에너미가 있는경우
	if (enemyREF)
	{
		DestroyEnemy();
	}
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	enemyREF = GetWorld()->SpawnActor<ABaseEnemy>(enemy_BP, FVector(0.0f, 0.0f, 5000.f), FRotator::ZeroRotator, params);
	if (enemyREF)
	{
		enemyREF->LoadData(bodyRowName, weapon1RowName, weapon2RowName, gearRowName, AIData);
	}

	if (rangeActor)
	{
		rangeActor->Init(enemyREF);
	}

	FTimerHandle spawnTimer;
	GetWorld()->GetTimerManager().SetTimer(spawnTimer, FTimerDelegate::CreateLambda([&](){
		if (enemyREF)
		{
			enemyREF->SetActorLocation(spawnPoint->GetActorLocation());
		}
	}), 0.125f, false);
}

void ATestRoomGameMode::ShowAIUI()
{
	AIWidget = CreateWidget<UTestRoomAIWidget>(GetWorld(), AIWidget_bp);
	AIWidget->AddToViewport();
}

void ATestRoomGameMode::ShowSettingUI()
{
	if (SetWidget == nullptr)
	{
		SetWidget = CreateWidget<UTestRoomSetWidget>(GetWorld(), SetWidget_bp);
		SetWidget->AddToViewport();
	}
	else
	{
		SetWidget->SetVisibility(ESlateVisibility::Visible);
	}
	SpawnEnemy();

	if (enemyREF)
	{
		SetWidget->Init(enemyREF->bodyRowName, enemyREF->weapon1RowName, enemyREF->weapon2RowName, enemyREF->gearRowName);
		SetWidget->SetEnemySpec(-1, "");
	}

}

void ATestRoomGameMode::ShowSaveUI()
{
	if (SaveWidget == nullptr)
	{
		SaveWidget = CreateWidget<UTestRoomSaveWidget>(GetWorld(), SaveWidget_bp);
		SaveWidget->AddToViewport();
	}
	else
	{
		SaveWidget->SetVisibility(ESlateVisibility::Visible);
	}

	SaveWidget->CheakLoadedName();


}

void ATestRoomGameMode::ShowLoadUI()
{
	if (LoadWidget == nullptr)
	{
		LoadWidget = CreateWidget<UTestRoomLoadWidget>(GetWorld(), LoadWidget_bp);
		LoadWidget->AddToViewport();
	}
	else
	{
		LoadWidget->SetVisibility(ESlateVisibility::Visible);
	}

	SpawnEnemy();

	LoadWidget->MoveToEnemy();
	LoadWidget->ShowNormalEnemyList();
}

void ATestRoomGameMode::SetEnemySetting(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName)
{
	bodyRowName = _bodyRowName;
	weapon1RowName = _weapon1RowName;
	weapon2RowName = _weapon2RowName;
	gearRowName = _gearRowName;

	if (enemyREF)
	{
		enemyREF->LoadData(bodyRowName, weapon1RowName, weapon2RowName, gearRowName, AIData);
		if (rangeActor)
		{
			rangeActor->Init(enemyREF);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Set No Enemy!"));
		}
	}
	else {
		SpawnEnemy();
		if (rangeActor)
		{
			rangeActor->Init(enemyREF);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Set No Enemy!"));
		}
	}
}

void ATestRoomGameMode::SetAI(FAIStat _AIData)
{
	AIData = _AIData;
	if (enemyREF)
	{
		enemyREF->AIData = AIData;
		if (rangeActor)
		{
			rangeActor->Init(enemyREF);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("AI No Enemy!"));
		}
	}

}
