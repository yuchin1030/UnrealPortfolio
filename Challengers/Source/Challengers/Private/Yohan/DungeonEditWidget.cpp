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
	
	// �÷��̾� ������
	/*pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	dc = Cast<ADungeonEditCharacter>(pc->GetSpectatorPawn());*/

	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}

	// ���� ó�� ������ �� ��� �����͸� �����
	CloseAllEditor();

	// �ٷ� ���� ���� UI ����
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

// ĳ���Ͱ� ������ �ִ� ���� ������ ������Ʈ�� OpenMap�� �����Ѵ�
void UDungeonEditWidget::OpenSteamPunkMap()
{	
	if (dc != nullptr)
	{		
		// ���� Ÿ�� ����
		dunType = "Steam Punk";
		// ĳ���Ͱ� ������ �ִ� ���������� ������Ʈ���� ������ũ �� �����ϱ�
		dc->dungeonEditComponent->OpenMap(FName("Airship"));
		
		// �ε�â
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
		// ���� Ÿ�� ����
		dunType = "Diesel Punk";
		// ĳ���Ͱ� ������ �ִ� ���������� ������Ʈ���� ������ũ �� �����ϱ�
		dc->dungeonEditComponent->OpenMap(FName("DisselPunk"));

		// �ε�â
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
		// ���� Ÿ�� ����
		dunType = "Cyber Punk";
		// ĳ���Ͱ� ������ �ִ� ���������� ������Ʈ���� ���̹���ũ �� �����ϱ�
		dc->dungeonEditComponent->OpenMap(FName("CyberPunk01"));

		// �ε�â
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
	// ���� ����UI�� ����
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
				listTemp = CreateWidget<UEnemyListWidget>(this, EnemyListUI_BP);

				// ���� ���Ͱ� �ƴ϶��
				if (false == gi->loadedEnemyDataList[i].bIsBossType)
				{
					// ����Ʈ �� �̹��� ����
					image_enemyBack->SetVisibility(ESlateVisibility::Visible);
					image_enemyBack_off->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack->SetVisibility((ESlateVisibility::Hidden));
					image_bossBack_off->SetVisibility(ESlateVisibility::Visible);
					image_dunBack->SetVisibility((ESlateVisibility::Hidden));
					image_dunBack_off->SetVisibility(ESlateVisibility::Visible);

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

		
	}
	index = 0;
}

void UDungeonEditWidget::ShowBossEnemyList()
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
			listTemp = CreateWidget<UEnemyListWidget>(this, EnemyListUI_BP);

			// ���� ���Ͷ��
			if (true == loadDataList[i].bIsBossType)
			{
				// ����Ʈ �� �̹��� ����
				image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
				image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
				image_bossBack->SetVisibility((ESlateVisibility::Visible));
				image_bossBack_off->SetVisibility(ESlateVisibility::Hidden);
				image_dunBack->SetVisibility((ESlateVisibility::Hidden));
				image_dunBack_off->SetVisibility(ESlateVisibility::Visible);

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
	index = 1;
}

void UDungeonEditWidget::SelectCancel()
{
	// ������Ʈ�� ���õ� ���ʹ̸� �ı��Ѵ�
	if (dc->dungeonEditComponent->SelectedEnemy)
	{
		dc->dungeonEditComponent->SelectedEnemy->Died(false);

		dc->dungeonEditComponent->SelectedEnemy = nullptr;

		dc->dungeonEditComponent->bIsObjectFixed = true;

		// ���콺 Ŀ�� ���̰� �Ѵ�
		pc->bShowMouseCursor = true;

		// ��ǲ��带 Game/UI���� FInputModeGameAndUI�� �ٲ��ش�
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
	// �̸� �Է� �ϴ� �� Ȱ��ȭ
	dunNameCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UDungeonEditWidget::LoadDungeonList()
{
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		loadDunList.Empty();
		// �����Ǿ� �ִ� ���� ������ �ε�
		gi->LoadDungeonData();
		loadDunList = gi->loadedDunData;

		// ����Ʈ �� �̹��� ����
		image_enemyBack->SetVisibility(ESlateVisibility::Hidden);
		image_enemyBack_off->SetVisibility((ESlateVisibility::Visible));
		image_bossBack->SetVisibility((ESlateVisibility::Hidden));
		image_bossBack_off->SetVisibility(ESlateVisibility::Visible);
		image_dunBack->SetVisibility((ESlateVisibility::Visible));
		image_dunBack_off->SetVisibility((ESlateVisibility::Hidden));

		enemyScroll->ClearChildren();

		// ���� Ÿ�Ժ� �迭 ����
		TArray<FDunInfo> steamList;
		TArray<FDunInfo> disList;
		TArray<FDunInfo> cyberList;

		// ���� Ÿ�Ժ��� ������ �з�
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

		// Ÿ�Ժ� ����Ʈ ���� �Լ�
		auto CreateDungeonListWidgets = [&](const TArray<FDunInfo>& dungeonList)
			{
				for (int i = 0; i < dungeonList.Num(); i++)
				{
					dunListTemp = CreateWidget<UDungeonListWidget>(this, dunListUI_BP);

					if (dunListTemp)
					{
						// ���� ����Ʈ ���� �ε��� �ο�
						dunListTemp->dunIndex = i;

						// ���� �̸� �ο�
						FText nameText = FText::FromString(dungeonList[i].dunName);
						dunListTemp->dungeonNameText->SetText(nameText);

						// ���� Ÿ�� �ο�
						FText typeText = FText::FromString(dungeonList[i].dunType);
						dunListTemp->dungeonTypeText->SetText(typeText);

						// ���� ����Ʈ ���� ���� ���� �ο�
						dunListTemp->_dunName = dungeonList[i].dunName;
						dunListTemp->_dunType = dungeonList[i].dunType;
						dunListTemp->_savedEnemys = dungeonList[i].savedEnemys;
						dunListTemp->dungeonCostText->SetText(FText::FromString(FString::FromInt(dungeonList[i].dunTotalCost)));

						enemyScroll->AddChild(dunListTemp);
					}
				}
			};

		// Ÿ�Ժ��� ����Ʈ ���� ȣ��
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
	// ������ ������ ���� �̸� ����
	dunName = editableText_DunName->GetText().ToString();

	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{	
		// ���� �̸����� ���� ���̺�
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
	// ������ OpenLevel �Ѵ�.
	// ������ �ӽ÷� �׽�Ʈ������ �̵�

	// �ε� â ����
	gi->bSLoading = true;

	UGameplayStatics::OpenLevel(this, FName("SingleMap"));
	// ��ǲ��带 Game/UI���� GameOnly�� �ٲ��ش�
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

