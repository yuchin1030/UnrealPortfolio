// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DE_EnemyControlWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "Yohan/DungeonEditComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include "Yohan/DungeonEditCharacter.h"

void UDE_EnemyControlWidget::NativeConstruct()
{
	Super::NativeConstruct();

	button_move->OnClicked.AddDynamic(this, &UDE_EnemyControlWidget::Move);
	button_delete->OnClicked.AddDynamic(this, &UDE_EnemyControlWidget::Delete);

	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}
}

void UDE_EnemyControlWidget::Move()
{
	dc->dungeonEditComponent->SetEnemyMove();
}

void UDE_EnemyControlWidget::Delete()
{
	dc->dungeonEditComponent->SetEnemyDelete();
}
