// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomAIWidget.h"
#include "CHR/TestRoomGameMode.h"
#include "CHR/DrawRangeActor.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/WidgetAnimation.h"

void UTestRoomAIWidget::NativeConstruct()
{
	TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());

	AICancelBtn->OnClicked.AddDynamic(this, &UTestRoomAIWidget::ClickCancelButton);
	AISaveBtn->OnClicked.AddDynamic(this, &UTestRoomAIWidget::ClickSaveButton);

	Button_1->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered1);
	Button_2->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered2);
	Button_3->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered3);
	Button_4->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered4);
	Button_5->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered5);
	Button_6->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered6);
	Button_7->OnHovered.AddDynamic(this, &UTestRoomAIWidget::OnHovered7);

	Button_1->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered1);
	Button_2->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered2);
	Button_3->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered3);
	Button_4->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered4);
	Button_5->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered5);
	Button_6->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered6);
	Button_7->OnUnhovered.AddDynamic(this, &UTestRoomAIWidget::OnUnhovered7);

	if (TRGM) {
		TRGM->SpawnEnemy();
		if (TRGM->enemyREF) {
			BattleDistSlide->SetValue(TRGM->enemyREF->AIData.battleDist);
			RandomAreaSlide->SetValue(TRGM->enemyREF->AIData.randomArea);
			MoveRateSlide->SetValue(TRGM->enemyREF->AIData.moveRate);
			PlayerFindDistSlide->SetValue(TRGM->enemyREF->AIData.playerFindDist);
			TargetChangeRateSlide->SetValue(TRGM->enemyREF->AIData.targetChangeRate);
			Phase2RateSlide->SetValue(TRGM->enemyREF->AIData.phase2Rate);
			Phase3RateSlide->SetValue(TRGM->enemyREF->AIData.phase3Rate);
		}
	}
}

void UTestRoomAIWidget::ClickSaveButton()
{
	//������ AI ���� ���� �Ѱ��ش�.
	newAIData.battleDist = BattleDistSlide->GetValue();
	newAIData.randomArea = RandomAreaSlide->GetValue();
	newAIData.moveRate = MoveRateSlide->GetValue();
	newAIData.playerFindDist = PlayerFindDistSlide->GetValue();
	newAIData.targetChangeRate = TargetChangeRateSlide->GetValue();
	newAIData.phase2Rate = Phase2RateSlide->GetValue();
	newAIData.phase3Rate = Phase3RateSlide->GetValue();

	//3������� 2����� �ʰ� �ߵ��ϸ� �̻��ؼ� ����
	if (newAIData.phase2Rate <= newAIData.phase3Rate) {
		newAIData.phase3Rate = newAIData.phase2Rate - 0.1;
	}

	//���� �̵����� �����Ͽ� �̵��� �νĹ��� ������ ������ �ʵ��� �Ѵ�.
	if (newAIData.battleDist * (1.0f + newAIData.randomArea) > newAIData.playerFindDist) {
		newAIData.battleDist = newAIData.playerFindDist / (1.0f + newAIData.randomArea);
	}

	if (TRGM)
	{
		TRGM->SetAI(newAIData);
		PlayAnimation(showSaveComplete);
	}
}

void UTestRoomAIWidget::ClickCancelButton()
{
	for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
		AChallengersCharacter* player = *iter;
		player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		player->bShowAISetting = false;
	}
	
	AMainPlayerController* pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;
	}
	
	RemoveFromParent();
	//SetVisibility(ESlateVisibility::Hidden);
}

// ������ ���� ��ư�� ���콺 �ø� �� ���� ������ ��ư��
void UTestRoomAIWidget::OnHovered1()
{
	Image_1->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered1()
{
	Image_1->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered2()
{
	Image_2->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered2()
{
	Image_2->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered3()
{
	Image_3->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered3()
{
	Image_3->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered4()
{
	Image_4->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered4()
{
	Image_4->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered5()
{
	Image_5->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered5()
{
	Image_5->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered6()
{
	Image_6->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered6()
{
	Image_6->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomAIWidget::OnHovered7()
{
	Image_7->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomAIWidget::OnUnhovered7()
{
	Image_7->SetVisibility(ESlateVisibility::Hidden);
}