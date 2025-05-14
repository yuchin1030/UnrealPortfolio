// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/MoveToDungeonWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "OurGameInstance.h"
#include <MainPlayerController.h>
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"

void UMoveToDungeonWidget::NativeConstruct()
{
	button_MoveToDungeon->OnClicked.AddDynamic(this, &UMoveToDungeonWidget::MoveToDungeon);
	button_MoveToDungeon->OnHovered.AddDynamic(this, &UMoveToDungeonWidget::MoveToDungeon_Ho);
	button_MoveToDungeon->OnUnhovered.AddDynamic(this, &UMoveToDungeonWidget::MoveToDungeon_Unho);

	button_close->OnClicked.AddDynamic(this, &UMoveToDungeonWidget::CloseWidget);
	button_close->OnHovered.AddDynamic(this, &UMoveToDungeonWidget::CloseWidget_Ho);
	button_close->OnUnhovered.AddDynamic(this, &UMoveToDungeonWidget::CloseWidget_Unho);

	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	pc->bShowMouseCursor = true;
	pc->SetInputMode(FInputModeUIOnly());
}

void UMoveToDungeonWidget::MoveToDungeon()
{
	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	// 게임 인스턴스의 던전 타입대로 서버 트래블한다
	if (gi)
	{
		gi->bdunloadStart = true;
		gi->MoveToDungeon();
		auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
		pc->SetInputMode(FInputModeUIOnly());
	}

}

void UMoveToDungeonWidget::MoveToDungeon_Ho()
{
	UUserWidget::PlayAnimation(StartAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UMoveToDungeonWidget::MoveToDungeon_Unho()
{
	UUserWidget::PlayAnimation(StartAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
}

void UMoveToDungeonWidget::CloseWidget()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	RemoveFromParent();
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	pc->bShowMouseCursor = false;
	pc->SetInputMode(FInputModeGameOnly());


}

void UMoveToDungeonWidget::CloseWidget_Ho()
{
	UUserWidget::PlayAnimation(CloseAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UMoveToDungeonWidget::CloseWidget_Unho()
{
	UUserWidget::PlayAnimation(CloseAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);

}
