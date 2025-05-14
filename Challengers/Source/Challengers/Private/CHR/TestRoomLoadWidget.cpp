// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomLoadWidget.h"
#include "CHR/ListViewItem/TREnemyList.h"
#include "CHR/TestRoomGameMode.h"
#include "BJK/MainPlayerWidget.h"
#include "OurGameInstance.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraActor.h>
#include "Components/WidgetComponent.h"

void UTestRoomLoadWidget::NativeConstruct()
{
	TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	button_normalEnemy->OnClicked.AddDynamic(this, &UTestRoomLoadWidget::ShowNormalEnemyList);
	button_bossEnemy->OnClicked.AddDynamic(this, &UTestRoomLoadWidget::ShowBossEnemyList);
	button_Return->OnClicked.AddDynamic(this, &UTestRoomLoadWidget::CloseWidget);
	RemoveYes->OnClicked.AddDynamic(this, &UTestRoomLoadWidget::WantRemove);
	RemoveNo->OnClicked.AddDynamic(this, &UTestRoomLoadWidget::NoWantRemove);
	
	for (TActorIterator<ACameraActor> iter(GetWorld()); iter; ++iter) {
		if (iter->ActorHasTag(FName("Load")))
		{
			settingCamera = *iter;
			break;
		}
	}
}

void UTestRoomLoadWidget::MoveToEnemy()
{
	if (pc && settingCamera)
	{
		pc->SetViewTargetWithBlend(settingCamera, 1.0f);
	}
}

void UTestRoomLoadWidget::ShowNormalEnemyList()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowNormalEnemyList"));
	// ���ʹ� ���̺� ������ ������ �ִ� ���� �ν��Ͻ��� ĳ�����Ѵ�
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDataList.Empty();

		// ���̺� �����͸� ������ �´�
		gi->LoadEnemyData();
		loadDataList = gi->loadedEnemyDataList;

		// ���ʹ� ����Ʈ�� �ʱ�ȭ �Ѵ�
		enemyScroll->ClearChildren();

		// loadedEnemyDataList�� ����� 0�� �ƴҶ��� �����ϱ�
		if (gi->loadedEnemyDataList.Num() > 0)
		{
			for (int i = 0; i < gi->loadedEnemyDataList.Num(); i++)
			{
				// ���ʹ� ������ ����Ʈ ������ �����
				listTemp = CreateWidget<UTREnemyList>(this, EnemyListUI_BP);
				
				// ���� ���Ͱ� �ƴ϶��
				if (false == gi->loadedEnemyDataList[i].bIsBossType)
				{
					// ����Ʈ �� �̹��� ����
					image_enemyBack->SetVisibility(ESlateVisibility::Visible);
					image_enemyBack_off->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack_off->SetVisibility(ESlateVisibility::Visible);

					if (listTemp)
					{
						// �̸� �����͸� ������ �ͼ� �ִ´�
						FText nameText = FText::FromString(gi->loadedEnemyDataList[i].name);
						listTemp->enemyNameText->SetText(nameText);
						// �ڽ�Ʈ �����͸� ������ �ͼ� �ִ´�
						FText costText = FText::AsNumber(gi->loadedEnemyDataList[i].totalCost);
						listTemp->enemyCostText->SetText(costText);

						// ���ʹ� Ÿ���� ���´�
						FString _eType = "Normal";
						FText eType = FText::FromString(_eType);
						listTemp->enemyTypeText->SetText(eType);

						// ���̺�� ���ʹ� �����͸� �Ҵ��Ѵ�. ���߿� �̴�� �����ϱ� ����
						listTemp->_bodyRowName = loadDataList[i].bodyRowName;
						listTemp->_weapon1RowName = loadDataList[i].weapon1RowName;
						listTemp->_weapon2RowName = loadDataList[i].weapon2RowName;
						listTemp->_gearRowName = loadDataList[i].gearRowName;
						listTemp->_AIData = loadDataList[i].AIData;
						listTemp->_name = loadDataList[i].name;
						listTemp->_bIsBossType = loadDataList[i].bIsBossType;

						// ������� ����Ʈ ������ ��ũ�ѿ� ��´�
						enemyScroll->AddChild(listTemp);

					}
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Normal Enemy"));
		}
	}

	image_enemyBack->SetVisibility(ESlateVisibility::Visible);
	image_enemyBack_off->SetVisibility(ESlateVisibility::Hidden);
	image_bossBack->SetVisibility(ESlateVisibility::Hidden);
	image_bossBack_off->SetVisibility(ESlateVisibility::Visible);
}

void UTestRoomLoadWidget::ShowBossEnemyList()
{
	// ���ʹ� ���̺� ������ ������ �ִ� ���� �ν��Ͻ��� ĳ�����Ѵ�
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDataList.Empty();
		// ���̺� �����͸� ������ �´�
		gi->LoadEnemyData();
		loadDataList = gi->loadedEnemyDataList;

		// ���ʹ� ����Ʈ�� �ʱ�ȭ �Ѵ�
		enemyScroll->ClearChildren();

		for (int i = 0; i < loadDataList.Num(); i++)
		{
			// ���ʹ� ������ ����Ʈ ������ �����
			listTemp = CreateWidget<UTREnemyList>(this, EnemyListUI_BP);

			// ���� ���Ͷ��
			if (true == loadDataList[i].bIsBossType)
			{
				// ����Ʈ �� �̹��� ����
				image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
				image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
				image_bossBack->SetVisibility((ESlateVisibility::Visible));
				image_bossBack_off->SetVisibility(ESlateVisibility::Hidden);
				
				if (listTemp)
				{
					// �ڱ� �ε��� �ο�
					listTemp->enemyIndex = i;

					// �̸� �����͸� ������ �ͼ� �ִ´�
					FText nameText = FText::FromString(loadDataList[i].name);
					listTemp->enemyNameText->SetText(nameText);

					// �ڽ�Ʈ �����͸� ������ �ͼ� �ִ´�
					FText costText = FText::AsNumber(loadDataList[i].totalCost);
					listTemp->enemyCostText->SetText(costText);

					// ���ʹ� Ÿ���� ���´�
					FString _eType = "Boss";
					FText eType = FText::FromString(_eType);
					listTemp->enemyTypeText->SetText(eType);

					// ���̺�� ���ʹ� �����͸� �Ҵ��Ѵ�. ���߿� �̴�� �����ϱ� ����
					listTemp->_bodyRowName = loadDataList[i].bodyRowName;
					listTemp->_weapon1RowName = loadDataList[i].weapon1RowName;
					listTemp->_weapon2RowName = loadDataList[i].weapon2RowName;
					listTemp->_gearRowName = loadDataList[i].gearRowName;
					listTemp->_AIData = loadDataList[i].AIData;
					listTemp->_name = loadDataList[i].name;
					listTemp->_bIsBossType = loadDataList[i].bIsBossType;

					// ������� ����Ʈ ������ ��ũ�ѿ� ��´�
					enemyScroll->AddChild(listTemp);

				}
			}
		}
	}
	image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
	image_enemyBack_off->SetVisibility(ESlateVisibility::Visible);
	image_bossBack->SetVisibility(ESlateVisibility::Visible);
	image_bossBack_off->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomLoadWidget::CloseWidget()
{
	if (pc && settingCamera)
	{
		pc->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f);
	}

	SetVisibility(ESlateVisibility::Hidden);

	FTimerHandle canMoveTimer;
	GetWorld()->GetTimerManager().SetTimer(canMoveTimer, FTimerDelegate::CreateLambda([&]() {
		for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
			AChallengersCharacter* player = *iter;
			player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			player->bShowLoadWidget = false;
			player->NameComp->SetVisibility(true);
		}

		if (pc)
		{
			if (pc->mainplayerWidget)
			{
				pc->mainplayerWidget->SetVisibility(ESlateVisibility::Visible);
			}
			pc->SetInputMode(FInputModeGameOnly());
			pc->bShowMouseCursor = false;
		}
		}), 1.0f, false);
}

void UTestRoomLoadWidget::WantRemove()
{
	listTemp->RemoveEnemy(name);
	CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Hidden);
}

void UTestRoomLoadWidget::NoWantRemove()
{
	CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Hidden);
}
