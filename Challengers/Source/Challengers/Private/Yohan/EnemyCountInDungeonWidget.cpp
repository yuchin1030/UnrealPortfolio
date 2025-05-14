// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/EnemyCountInDungeonWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>
#include "Components/WidgetSwitcher.h"
#include "Yohan/OurGameStateBase.h"
#include "Components/ProgressBar.h"
#include "OurGameModeBase.h"

void UEnemyCountInDungeonWidget::NativeConstruct()
{
	Super::NativeConstruct();
		
	gs = Cast<AOurGameStateBase>(GetWorld()->GetGameState());
	gm = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
	

	
}

void UEnemyCountInDungeonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FString totalString = FString::FromInt(gs->_enemyTotal);
	totalText = FText::FromString(totalString);
	text_enemyTotal->SetText(totalText);

	FString curString = FString::FromInt(gs->_enemyCurrent);
	curText = FText::FromString(curString);
	text_enemyCur->SetText(curText);

	text_min->SetText(UKismetTextLibrary::Conv_IntToText((int)(gs->_cleatTimer) / 60, false, true, 2, 2));
	text_sec->SetText(UKismetTextLibrary::Conv_IntToText((int)(gs->_cleatTimer) % 60, false, true, 2, 2));

	ProgressBar_Timer->SetPercent(gs->_cleatTimer /180);

}

void UEnemyCountInDungeonWidget::ApplyBuff(int32 BuffNum)
{
	WidgetSwitcher_ApplyBuff->SetActiveWidgetIndex(BuffNum);
}
