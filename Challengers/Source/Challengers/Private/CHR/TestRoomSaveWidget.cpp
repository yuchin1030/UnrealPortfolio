// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomSaveWidget.h"
#include "CHR/BaseEnemy.h"
#include "CHR/TestRoomGameMode.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "BJK/MainPlayerWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>

void UTestRoomSaveWidget::NativeConstruct()
{
	Myplayer = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());

	SaveYesButton->OnClicked.AddDynamic(this, &UTestRoomSaveWidget::FinalSaveYes);
	SaveNoButton->OnClicked.AddDynamic(this, &UTestRoomSaveWidget::FinalSaveNo);

	if (Myplayer)
	{
		TextBlock_CurrentGold->SetText(FText::AsNumber(Myplayer->playerGold));
	}

}

void UTestRoomSaveWidget::CheakLoadedName()
{
	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (TRGM) {
		TRGM->SpawnEnemy();
		if (TRGM->currentEnemyName != "") {
			InputEnemyName->SetText(FText::FromString(TRGM->currentEnemyName));
		}
		TextBlock_CostTotal->SetText(FText::AsNumber(TRGM->enemyREF->enemySpec.totalCost));
	}
}

void UTestRoomSaveWidget::FinalSaveYes()
{
	ABaseEnemy* Enemy = nullptr;
	for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		Enemy = *it;
	}
	
	UOurGameInstance* OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	FString EnemyName = InputEnemyName->GetText().ToString();

	if (OG && Enemy)
	{
		OG->SaveEnemyData(EnemyName, Enemy->enemySpec.bIsBossType, Enemy->enemySpec.totalCost, Enemy->bodyRowName, Enemy->weapon1RowName, Enemy->weapon2RowName, Enemy->gearRowName, Enemy->AIData);

		PlayAnimation(showSaveComplete);
	
		// 플레이어 소유 골드 감소
		if (Myplayer)
		{
			Myplayer->playerGold -= Enemy->enemySpec.totalCost;
			OG->SavePlayerInfoData(Myplayer->playerName, Myplayer->playerLevel, Myplayer->playerGold, Myplayer->playerCurrentExp, Myplayer->playerMaxExp, Myplayer->enemyCost, Myplayer->weaponLevel, Myplayer->currentWeaponStat, Myplayer->nextWeaponStat, Myplayer->upgWeaponNeedGold);
		}
	}


	FTimerHandle menuCloseTimer;
	GetWorld()->GetTimerManager().SetTimer(menuCloseTimer, this, &UTestRoomSaveWidget::FinalSaveNo, 2.0f, false);
}

void UTestRoomSaveWidget::FinalSaveNo()
{
	for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
		AChallengersCharacter* player = *iter;
		player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		player->bShowSaveWidget = false;
	}

	AMainPlayerController* pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		if (pc->mainplayerWidget)
		{
			pc->mainplayerWidget->SetVisibility(ESlateVisibility::Visible);
		}
		pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;
	}

	SetVisibility(ESlateVisibility::Hidden);
}
