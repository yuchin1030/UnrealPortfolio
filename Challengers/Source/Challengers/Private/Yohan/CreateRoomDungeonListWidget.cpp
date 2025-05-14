// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/CreateRoomDungeonListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "OurGameInstance.h"
#include "CHR/CreateRoomWidget.h"

void UCreateRoomDungeonListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	button_createDungeon->OnClicked.AddDynamic(this, &UCreateRoomDungeonListWidget::SendDungeonName);
	button_createDungeon->OnHovered.AddDynamic(this, &UCreateRoomDungeonListWidget::OnHovered);
	button_createDungeon->OnUnhovered.AddDynamic(this, &UCreateRoomDungeonListWidget::OnUnHovered);
}

void UCreateRoomDungeonListWidget::SendDungeonName()
{

	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		// 게임 인스턴스의 createDunName을 저장되어 있는 던전의 이름으로 설정한다
		gi->createDunName = _dunName;
		gi->createDunType = _dunType;
		gi->createDunCost = _dunCost;
	}
	UCreateRoomWidget* scroll = Cast<UCreateRoomWidget>(GetParent()->GetOuter()->GetOuter());
	if (scroll)
	{
		scroll->Allfalse();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Scroll"));
	}
	Show = true;

}

void UCreateRoomDungeonListWidget::OnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UCreateRoomDungeonListWidget::OnUnHovered()
{
	if (!Show)
	{
		UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
	}
}




