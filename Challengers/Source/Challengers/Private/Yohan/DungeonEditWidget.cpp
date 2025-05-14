// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonEditWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "ChallengersCharacter.h"
#include "Yohan/DungeonEditComponent.h"
#include "Kismet/GameplayStatics.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanel.h>
#include "OurGameModeBase.h"
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>
#include "Yohan/EnemyListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "CHR/EnemySaveData.h"
#include "Yohan/DungeonEditCharacter.h"
#include "EngineUtils.h"
#include "Yohan/SaveDungeonData.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableTextBox.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/HorizontalBox.h>
#include "Yohan/DungeonListWidget.h"
#include "Yohan/DungeonEditGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>
#include "Components/Image.h"
#include "LoadingWidget.h"


void UDungeonEditWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	button_SteamPunk->OnClicked.AddDynamic(this, &UDungeonEditWidget::OpenSteamPunkMap);
	button_DisselPunk->OnClicked.AddDynamic(this, &UDungeonEditWidget::OpenDisselPunkMap);
	button_CyberPunk->OnClicked.AddDynamic(this, &UDungeonEditWidget::OpenCyberPunkMap);
	button_normalEnemy->OnClicked.AddDynamic(this, &UDungeonEditWidget::ShowNormalEnemyList);
	button_bossEnemy->OnClicked.AddDynamic(this, &UDungeonEditWidget::ShowBossEnemyList);
	button_SpawnCancel->OnClicked.AddDynamic(this, &UDungeonEditWidget::SelectCancel);
	button_EditCancel->OnClicked.AddDynamic(this, &UDungeonEditWidget::ReturnToTown);
	button_saveDugeon->OnClicked.AddDynamic(this, &UDungeonEditWidget::SaveDungeon);
	button_loadDugeon_test->OnClicked.AddDynamic(this,&UDungeonEditWidget::LoadDungeonList);
	button_DunName->OnClicked.AddDynamic(this, &UDungeonEditWidget::SaveDungeonName);
	button_closeSelect->OnClicked.AddDynamic(this, &UDungeonEditWidget::ReturnToTown);
	Button_Yes->OnClicked.AddDynamic(this, &UDungeonEditWidget::WantHome);
	Button_No->OnClicked.AddDynamic(this, &UDungeonEditWidget::NoWantHome);
	RemoveYes->OnClicked.AddDynamic(this, &UDungeonEditWidget::WantRemove);
	RemoveNo->OnClicked.AddDynamic(this, &UDungeonEditWidget::NoWantRemove);
	button_closeDunSave->OnClicked.AddDynamic(this, &UDungeonEditWidget::RemoveSaveDungeonName);
	
	// 플레이어 가져옴
	/*pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	dc = Cast<ADungeonEditCharacter>(pc->GetSpectatorPawn());*/

	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}

	// 게임 처음 시작할 때 모든 에디터를 숨긴다
	CloseAllEditor();

	// 바로 던전 선택 UI 띄우기
	OpenLevelSelect();
	
	pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	pc->bShowMouseCursor = true;

	gm = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode());

	CanvasPannel_ReturnHome->SetVisibility(ESlateVisibility::Hidden);
	CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Hidden);
	System_Save->SetVisibility(ESlateVisibility::Hidden);
	DeleteDungeon->SetVisibility(ESlateVisibility::Hidden);
	DeleteMonster->SetVisibility(ESlateVisibility::Hidden);
	
}

void UDungeonEditWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	text_totalCost->SetText(UKismetTextLibrary::Conv_IntToText((int)gm->totalEnemyCost));
	text_curCost->SetText(UKismetTextLibrary::Conv_IntToText((int)gm->curEnemyCost));	
}

// 캐릭터가 가지고 있는 던전 에디터 컴포넌트의 OpenMap을 실행한다
void UDungeonEditWidget::OpenSteamPunkMap()
{	
	if (dc != nullptr)
	{		
		// 던전 타입 설정
		dunType = "Steam Punk";
		// 캐릭터가 가지고 있는 던전에디터 컴포넌트에서 스팀펑크 맵 실행하기
		dc->dungeonEditComponent->OpenMap(FName("Airship"));
		
		// 로딩창
		dc->dungeonEditComponent->loadingUI->Image_Steam->SetVisibility(ESlateVisibility::Visible);

		levelCanvas->SetVisibility(ESlateVisibility::Hidden);

		enemyListCanvas->SetVisibility((ESlateVisibility::Visible));

		image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
		image_bossBack_off->SetVisibility((ESlateVisibility::Visible));
		image_dunBack_off->SetVisibility((ESlateVisibility::Visible));

		image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
		image_bossBack->SetVisibility(ESlateVisibility::Hidden);
		image_dunBack->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dc = nullptr"));
	}
}

void UDungeonEditWidget::OpenDisselPunkMap()
{	
	if (dc != nullptr)
	{
		// 던전 타입 설정
		dunType = "Diesel Punk";
		// 캐릭터가 가지고 있는 던전에디터 컴포넌트에서 디젤펑크 맵 실행하기
		dc->dungeonEditComponent->OpenMap(FName("DisselPunk"));

		// 로딩창
		dc->dungeonEditComponent->loadingUI->Image_Dissel->SetVisibility(ESlateVisibility::Visible);

		levelCanvas->SetVisibility(ESlateVisibility::Hidden);

		enemyListCanvas->SetVisibility((ESlateVisibility::Visible));

		image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
		image_bossBack_off->SetVisibility((ESlateVisibility::Visible));
		image_dunBack_off->SetVisibility((ESlateVisibility::Visible));
		
		image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
		image_bossBack->SetVisibility(ESlateVisibility::Hidden);
		image_dunBack->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UDungeonEditWidget::OpenCyberPunkMap()
{
	if (dc != nullptr)
	{
		// 던전 타입 설정
		dunType = "Cyber Punk";
		// 캐릭터가 가지고 있는 던전에디터 컴포넌트에서 사이버펑크 맵 실행하기
		dc->dungeonEditComponent->OpenMap(FName("CyberPunk01"));

		// 로딩창
		dc->dungeonEditComponent->loadingUI->Image_Cyber->SetVisibility(ESlateVisibility::Visible);

		levelCanvas->SetVisibility(ESlateVisibility::Hidden);

		enemyListCanvas->SetVisibility((ESlateVisibility::Visible));

		image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
		image_bossBack_off->SetVisibility((ESlateVisibility::Visible));
		image_dunBack_off->SetVisibility((ESlateVisibility::Visible));

		image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
		image_bossBack->SetVisibility(ESlateVisibility::Hidden);
		image_dunBack->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UDungeonEditWidget::OpenLevelSelect()
{
	// 레벨 선택UI를 띄운다
	levelCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UDungeonEditWidget::CloseAllEditor()
{
	levelCanvas->SetVisibility((ESlateVisibility::Hidden));
	enemyListCanvas->SetVisibility((ESlateVisibility::Hidden));
	dunNameCanvas->SetVisibility((ESlateVisibility::Hidden));
	image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
	image_bossBack->SetVisibility(ESlateVisibility::Hidden);
	image_dunBack->SetVisibility(ESlateVisibility::Hidden);
}

void UDungeonEditWidget::ShowNormalEnemyList()
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
		
		// loadedEnemyDataList의 사이즈가 0이 아닐때만 접근하기
		if (gi->loadedEnemyDataList.Num() > 0)
		{
			for (int i = 0; i < gi->loadedEnemyDataList.Num(); i++)
			{
				// 에너미 데이터 리스트 위젯을 만든다
				listTemp = CreateWidget<UEnemyListWidget>(this, EnemyListUI_BP);

				// 보스 몬스터가 아니라면
				if (false == gi->loadedEnemyDataList[i].bIsBossType)
				{
					// 리스트 백 이미지 세팅
					image_enemyBack->SetVisibility(ESlateVisibility::Visible);
					image_enemyBack_off->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack_off->SetVisibility(ESlateVisibility::Visible);
					image_dunBack->SetVisibility((ESlateVisibility::Hidden));
					image_dunBack_off->SetVisibility(ESlateVisibility::Visible);

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

		
	}
	index = 0;
}

void UDungeonEditWidget::ShowBossEnemyList()
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
			listTemp = CreateWidget<UEnemyListWidget>(this, EnemyListUI_BP);

			// 보스 몬스터라면
			if (true == loadDataList[i].bIsBossType)
			{
				// 리스트 백 이미지 세팅
				image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
				image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
				image_bossBack->SetVisibility((ESlateVisibility::Visible));
				image_bossBack_off->SetVisibility(ESlateVisibility::Hidden);
				image_dunBack->SetVisibility((ESlateVisibility::Hidden));
				image_dunBack_off->SetVisibility(ESlateVisibility::Visible);

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
	index = 1;
}

void UDungeonEditWidget::SelectCancel()
{
	// 컴포넌트의 선택된 에너미를 파괴한다
	if (dc->dungeonEditComponent->SelectedEnemy)
	{
		dc->dungeonEditComponent->SelectedEnemy->Died(false);

		dc->dungeonEditComponent->SelectedEnemy = nullptr;

		dc->dungeonEditComponent->bIsObjectFixed = true;

		// 마우스 커서 보이게 한다
		pc->bShowMouseCursor = true;

		// 인풋모드를 Game/UI에서 FInputModeGameAndUI로 바꿔준다
		pc->SetInputMode(FInputModeGameAndUI());
	}

	ChildInit1();
}

void UDungeonEditWidget::ReturnToTown()
{


	CanvasPannel_ReturnHome->SetVisibility(ESlateVisibility::Visible);
}

void UDungeonEditWidget::SaveDungeon()
{
	// 이름 입력 하는 곳 활성화
	dunNameCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UDungeonEditWidget::LoadDungeonList()
{
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDunList.Empty();
		// 생성되어 있는 던전 데이터 로드
		gi->LoadDungeonData();
		loadDunList = gi->loadedDunData;

		// 리스트 백 이미지 세팅
		image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
		image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
		image_bossBack->SetVisibility((ESlateVisibility::Hidden));
		image_bossBack_off->SetVisibility(ESlateVisibility::Visible);
		image_dunBack->SetVisibility((ESlateVisibility::Visible));
		image_dunBack_off->SetVisibility((ESlateVisibility::Hidden));

		enemyScroll->ClearChildren();

		// 던전 타입별 배열 생성
		TArray<FDunInfo> steamList;
		TArray<FDunInfo> disList;
		TArray<FDunInfo> cyberList;

		// 던전 타입별로 데이터 분류
		for (int i = 0; i < loadDunList.Num(); i++)
		{
			if (loadDunList[i].dunType == "Steam Punk")
			{
				steamList.Add(loadDunList[i]);
			}
			else if (loadDunList[i].dunType == "Diesel Punk")
			{
				disList.Add(loadDunList[i]);
			}
			else if (loadDunList[i].dunType == "Cyber Punk")
			{
				cyberList.Add(loadDunList[i]);
			}
		}

		// 타입별 리스트 생성 함수
		auto CreateDungeonListWidgets = [&](const TArray<FDunInfo>& dungeonList)
			{
				for (int i = 0; i < dungeonList.Num(); i++)
				{
					dunListTemp = CreateWidget<UDungeonListWidget>(this, dunListUI_BP);

					if (dunListTemp)
					{
						// 던전 리스트 위젯 인덱스 부여
						dunListTemp->dunIndex = i;

						// 던전 이름 부여
						FText nameText = FText::FromString(dungeonList[i].dunName);
						dunListTemp->dungeonNameText->SetText(nameText);

						// 던전 타입 부여
						FText typeText = FText::FromString(dungeonList[i].dunType);
						dunListTemp->dungeonTypeText->SetText(typeText);

						// 던전 리스트 위젯 던전 정보 부여
						dunListTemp->_dunName = dungeonList[i].dunName;
						dunListTemp->_dunType = dungeonList[i].dunType;
						dunListTemp->_savedEnemys = dungeonList[i].savedEnemys;
						dunListTemp->dungeonCostText->SetText(FText::FromString(FString::FromInt(dungeonList[i].dunTotalCost)));

						enemyScroll->AddChild(dunListTemp);
					}
				}
			};

		// 타입별로 리스트 생성 호출
		if (dunType == "Steam Punk")
		{
			CreateDungeonListWidgets(steamList);
		}
		else if (dunType == "Diesel Punk")
		{
			CreateDungeonListWidgets(disList);
		}
		else if (dunType == "Cyber Punk")
		{
			CreateDungeonListWidgets(cyberList);
		}		
	}
	index = 2;
}

void UDungeonEditWidget::SaveDungeonName()
{
	// 유저가 설정한 던전 이름 저장
	dunName = editableText_DunName->GetText().ToString();

	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{	
		// 던전 이름으로 던전 세이브
		gi->SaveDungeon(dunName, dunType);
	}
	dunNameCanvas->SetVisibility(ESlateVisibility::Hidden);
	LoadDungeonList();

	System_Save->SetVisibility(ESlateVisibility::Visible);
	UUserWidget::PlayAnimation(Anim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UDungeonEditWidget::RemoveSaveDungeonName()
{
	dunNameCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UDungeonEditWidget::WantHome()
{
	dc->dungeonEditComponent->HideArea();
	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	// 마을로 OpenLevel 한다.
	// 지금은 임시로 테스트맵으로 이동

	// 로딩 창 띄우기
	gi->bSLoading = true;

	UGameplayStatics::OpenLevel(this, FName("SingleMap"));
	// 인풋모드를 Game/UI에서 GameOnly로 바꿔준다
	pc->SetInputMode(FInputModeGameOnly());
}


void UDungeonEditWidget::NoWantHome()
{
	CanvasPannel_ReturnHome->SetVisibility(ESlateVisibility::Hidden);
}

void UDungeonEditWidget::WantRemove()
{
	if(index == 0)
	{
		listTemp->RemoveEnemy(name);
	}
	else if (index == 1)
	{
		listTemp->RemoveEnemy(name);
	}
	else
	{ 
		dunListTemp->RemoveDungeon(name);
	}

	CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Hidden);
}

void UDungeonEditWidget::NoWantRemove()
{
	CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Hidden); 

}

void UDungeonEditWidget::ChildInit1()
{
	TArray<UWidget*> enemyList = enemyScroll->GetAllChildren();
	for(UWidget* enemy : enemyList){
		UEnemyListWidget* enemyWidget = Cast<UEnemyListWidget>(enemy);
		enemyWidget->Select1 = false;
	UE_LOG(LogTemp, Warning ,TEXT("ChildInit : %d"), enemyWidget->Select1);
	}

}

void UDungeonEditWidget::ChildInit2()
{
	TArray<UWidget*> DungeonList = enemyScroll->GetAllChildren();
	for (UWidget* Dungeon : DungeonList)
	{
		UDungeonListWidget* DungeonWidget = Cast<UDungeonListWidget>(Dungeon);
		DungeonWidget->Select2 = false;
	}
}

