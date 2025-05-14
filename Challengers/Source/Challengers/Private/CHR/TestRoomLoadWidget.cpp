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
	// 에너미 세이브 저장을 가지고 있는 게임 인스턴스를 캐스팅한다
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDataList.Empty();

		// 세이브 데이터를 가지고 온다
		gi->LoadEnemyData();
		loadDataList = gi->loadedEnemyDataList;

		// 에너미 리스트를 초기화 한다
		enemyScroll->ClearChildren();

		// loadedEnemyDataList의 사이즈가 0이 아닐때만 접근하기
		if (gi->loadedEnemyDataList.Num() > 0)
		{
			for (int i = 0; i < gi->loadedEnemyDataList.Num(); i++)
			{
				// 에너미 데이터 리스트 위젯을 만든다
				listTemp = CreateWidget<UTREnemyList>(this, EnemyListUI_BP);
				
				// 보스 몬스터가 아니라면
				if (false == gi->loadedEnemyDataList[i].bIsBossType)
				{
					// 리스트 백 이미지 세팅
					image_enemyBack->SetVisibility(ESlateVisibility::Visible);
					image_enemyBack_off->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack_off->SetVisibility(ESlateVisibility::Visible);

					if (listTemp)
					{
						// 이름 데이터를 가지고 와서 넣는다
						FText nameText = FText::FromString(gi->loadedEnemyDataList[i].name);
						listTemp->enemyNameText->SetText(nameText);
						// 코스트 데이터를 가지고 와서 넣는다
						FText costText = FText::AsNumber(gi->loadedEnemyDataList[i].totalCost);
						listTemp->enemyCostText->SetText(costText);

						// 에너미 타입을 적는다
						FString _eType = "Normal";
						FText eType = FText::FromString(_eType);
						listTemp->enemyTypeText->SetText(eType);

						// 세이브된 에너미 데이터를 할당한다. 나중에 이대로 스폰하기 위함
						listTemp->_bodyRowName = loadDataList[i].bodyRowName;
						listTemp->_weapon1RowName = loadDataList[i].weapon1RowName;
						listTemp->_weapon2RowName = loadDataList[i].weapon2RowName;
						listTemp->_gearRowName = loadDataList[i].gearRowName;
						listTemp->_AIData = loadDataList[i].AIData;
						listTemp->_name = loadDataList[i].name;
						listTemp->_bIsBossType = loadDataList[i].bIsBossType;

						// 만들어진 리스트 위젯을 스크롤에 담는다
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
	// 에너미 세이브 저장을 가지고 있는 게임 인스턴스를 캐스팅한다
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDataList.Empty();
		// 세이브 데이터를 가지고 온다
		gi->LoadEnemyData();
		loadDataList = gi->loadedEnemyDataList;

		// 에너미 리스트를 초기화 한다
		enemyScroll->ClearChildren();

		for (int i = 0; i < loadDataList.Num(); i++)
		{
			// 에너미 데이터 리스트 위젯을 만든다
			listTemp = CreateWidget<UTREnemyList>(this, EnemyListUI_BP);

			// 보스 몬스터라면
			if (true == loadDataList[i].bIsBossType)
			{
				// 리스트 백 이미지 세팅
				image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
				image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
				image_bossBack->SetVisibility((ESlateVisibility::Visible));
				image_bossBack_off->SetVisibility(ESlateVisibility::Hidden);
				
				if (listTemp)
				{
					// 자기 인덱스 부여
					listTemp->enemyIndex = i;

					// 이름 데이터를 가지고 와서 넣는다
					FText nameText = FText::FromString(loadDataList[i].name);
					listTemp->enemyNameText->SetText(nameText);

					// 코스트 데이터를 가지고 와서 넣는다
					FText costText = FText::AsNumber(loadDataList[i].totalCost);
					listTemp->enemyCostText->SetText(costText);

					// 에너미 타입을 적는다
					FString _eType = "Boss";
					FText eType = FText::FromString(_eType);
					listTemp->enemyTypeText->SetText(eType);

					// 세이브된 에너미 데이터를 할당한다. 나중에 이대로 스폰하기 위함
					listTemp->_bodyRowName = loadDataList[i].bodyRowName;
					listTemp->_weapon1RowName = loadDataList[i].weapon1RowName;
					listTemp->_weapon2RowName = loadDataList[i].weapon2RowName;
					listTemp->_gearRowName = loadDataList[i].gearRowName;
					listTemp->_AIData = loadDataList[i].AIData;
					listTemp->_name = loadDataList[i].name;
					listTemp->_bIsBossType = loadDataList[i].bIsBossType;

					// 만들어진 리스트 위젯을 스크롤에 담는다
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
