// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "OurGameInstance.h"
#include "Yohan/DungeonEditWidget.h"
#include "Yohan/DungeonEditCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include "Yohan/DungeonEditComponent.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanel.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UDungeonListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	button_enemySelect->OnClicked.AddDynamic(this, &UDungeonListWidget::LoadDungeon);
	button_enemySelect->OnHovered.AddDynamic(this, &UDungeonListWidget::OnHovered);
	button_enemySelect->OnUnhovered.AddDynamic(this, &UDungeonListWidget::OnUnHovered);

	button_Remove->OnClicked.AddDynamic(this, &UDungeonListWidget::QuestionRemove);

	EW = Cast<UDungeonEditWidget>(GetParent()->GetOuter()->GetOuter());
}

void UDungeonListWidget::OnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UDungeonListWidget::OnUnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
}

void UDungeonListWidget::LoadDungeon()
{
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	if (gi)
	{
		gi->LoadDungeon(_dunName, _dunType);
	}


	if (EW != nullptr)
	{
		EW->ChildInit2();
		Select2 = true;
	}
}

void UDungeonListWidget::RemoveDungeon(FString __dunName)
{

	auto * gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	if (gi)
	{
		gi->RemoveDungeon(__dunName);
	}

	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}

	if (dc)
	{
		dc->dungeonEditComponent->dungeonEditUI->LoadDungeonList();
	}

}

void UDungeonListWidget::QuestionRemove()
{
	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}
	dc->dungeonEditComponent->dungeonEditUI->name = _dunName;
	dc->dungeonEditComponent->dungeonEditUI->CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Visible);
	dc->dungeonEditComponent->dungeonEditUI->DeleteDungeon->SetVisibility(ESlateVisibility::Visible);
	dc->dungeonEditComponent->dungeonEditUI->DeleteMonster->SetVisibility(ESlateVisibility::Hidden);
}

void UDungeonListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Select2 == true)
	{
		Image_Select->SetOpacity(0.3);
	}
	else
	{
		Image_Select->SetOpacity(0);
	}
}


