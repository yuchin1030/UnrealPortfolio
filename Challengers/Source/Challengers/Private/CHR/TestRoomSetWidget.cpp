// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/TestRoomSetWidget.h"
#include "CHR/BaseEnemy.h"
#include "CHR/BaseWeapon.h"
#include "CHR/BaseGear.h"
#include "CHR/EnemyBodyStruct.h"
#include "CHR/WeaponStruct.h"
#include "CHR/GearStruct.h"
#include "CHR/TestRoomGameMode.h"
#include "BJK/MainPlayerWidget.h"
#include "GJY/WeaponList1.h"
#include "GJY/Weapon1Object.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "OurGameInstance.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/WidgetAnimation.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraActor.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "CHR/BaseEnemy.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Border.h>
#include "CHR/ListViewItem/TRBodyList.h"
#include "Components/WidgetComponent.h"

void UTestRoomSetWidget::NativeConstruct()
{

	SettingBtn->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ClickSettingBtn);
	ReturnBtn->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ClickReturnBtn);

	btn_Question->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ClickOpenHelpBtn);
	Button_HelpClose->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ClickCloseHelpBtn);

	EnemyBodyUI->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ShowEnemyBodyUI);
	EnemyWeaponUI1->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ShowEnemyWeaponUI1);
	EnemyWeaponUI2->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ShowEnemyWeaponUI2);
	EnemyAbilitySettingUI->OnClicked.AddDynamic(this, &UTestRoomSetWidget::ShowEnemyAbilitySettingUI);

	partUISwitcher->SetActiveWidgetIndex(0);
	partUISwitcher->SetVisibility(ESlateVisibility::Hidden);

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	gi = Cast<UOurGameInstance>(GetGameInstance());

	for (TActorIterator<ACameraActor> iter(GetWorld()); iter; ++iter) {
		if (iter->ActorHasTag(FName("Setting")))
		{
			settingCamera = *iter;
			break;
		}
	}
}

void UTestRoomSetWidget::Init(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName)
{
	bodyRowName = _bodyRowName;
	weapon1RowName = _weapon1RowName;
	weapon2RowName = _weapon2RowName;
	gearRowName = _gearRowName;
	
	if (player)
	{
		TextBlock_playerGold->SetText(FText::AsNumber(player->playerGold));
	}

	if (pc && settingCamera)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cam Move"));
		pc->SetViewTargetWithBlend(settingCamera, 1.0f);
	}
	else{
		if (pc == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No PC"));
		}

		if (settingCamera == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No settingCamera"));
		}
	}
}

void UTestRoomSetWidget::ClickSettingBtn()
{
	//게임모드에 저장한다
	if (TRGM)
	{
		if (!TRGM->enemyREF->enemySpec.bIsBossType && (TRGM->enemyREF->weapon2 != nullptr || TRGM->enemyREF->gear != nullptr))
		{
			PlayAnimation(canNotSelect);
			return;
		}

		TRGM -> SetEnemySetting(bodyRowName, weapon1RowName, weapon2RowName, gearRowName);
		PlayAnimation(showSaveComplete);
	}
}

// 마을로 돌아가는 부분.
void UTestRoomSetWidget::ClickReturnBtn()
{
	//세팅창을 닫는다
	if (pc && settingCamera)
	{
		pc->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f);
	}

	SetVisibility(ESlateVisibility::Hidden);

	FTimerHandle canMoveTimer;
	GetWorld()->GetTimerManager().SetTimer(canMoveTimer, FTimerDelegate::CreateLambda([&](){
		for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
			AChallengersCharacter* player = *iter;
			player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			player->bShowEnemySetting = false;
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

// 도움말 열기 버튼
void UTestRoomSetWidget::ClickOpenHelpBtn()
{
	Button_HelpClose->SetVisibility(ESlateVisibility::Visible);
	Image_HelpBackGround->SetVisibility(ESlateVisibility::Visible);
	Border_Help->SetVisibility(ESlateVisibility::Visible);
}
// 도움말 닫기
void UTestRoomSetWidget::ClickCloseHelpBtn()
{
	Button_HelpClose->SetVisibility(ESlateVisibility::Hidden);
	Image_HelpBackGround->SetVisibility(ESlateVisibility::Hidden);
	Border_Help->SetVisibility(ESlateVisibility::Hidden);
}

//에너미 몸체설정 부분
void UTestRoomSetWidget::ShowEnemyBodyUI()
{
	EnemyBodyListView->ClearListItems();

	EnemyBodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyBodySpec.DT_EnemyBodySpec'"));

	TArray<FbodySpec*> bodyData;

	EnemyBodyDataTable->GetAllRows<FbodySpec>(TEXT("GetAllRows"), bodyData);

	int32 normalNum = 1;
	int32 bossNum = 1;
	for (int32 i = 0; i < bodyData.Num(); i++)
	{
		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());
		WO->BodyObject = *bodyData[i];

		FString tempString;


		if (!WO->BodyObject.bIsBossType)
		{
			tempString = "NB";
			tempString += FString::FromInt(normalNum);
			normalNum++;
		}
		else
		{
			tempString = "BB";
			tempString += FString::FromInt(bossNum);
			bossNum++;
		}

		WO->_RowName = FName(tempString);

		WO->indexNum = i;


		EnemyBodyListView->AddItem(WO);
	}

	Image_On_Body->SetVisibility(ESlateVisibility::Visible);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	SwitcherUI->SetActiveWidgetIndex(0);

	if (TRGM->enemyREF->GetActorRotation().Yaw != 0.0f) {
		TRGM->RotateEnemy(true);
	}
}

//웨폰1번 리스트 선택 부분
void UTestRoomSetWidget::ShowEnemyWeaponUI1()
{

	//WeaponList에 표시되어야 할 목록. 이름: 데미지, 사거리, 쿨다운, 무게, 가격
	Weapon1ListView->ClearListItems();

	Weapon1ListDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyOneHandWeaponSpec.DT_EnemyOneHandWeaponSpec'"));

	TArray<FweaponSpec*> WeaponData;


	Weapon1ListDataTable->GetAllRows<FweaponSpec>(TEXT("GetAllRows"), WeaponData);

	for (int32 i = 0; i < WeaponData.Num(); i++)
	{
		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());

		WO->WeaponObject1 = *WeaponData[i];

		FString tempString = "W1_";
		tempString += FString::FromInt(i);

		WO->_RowName = FName(tempString);

		WO->indexNum = i;

		Weapon1ListView->AddItem(WO);
	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Visible);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	SwitcherUI->SetActiveWidgetIndex(1);

	if (TRGM->enemyREF->GetActorRotation().Yaw != 0.0f) {
		TRGM->RotateEnemy(true);
	}
}
//웨폰 2번 리스트 선택 부분
void UTestRoomSetWidget::ShowEnemyWeaponUI2()
{
	Weapon2ListView->ClearListItems();

	Weapon2ListDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyTwoHandWeaponSpec.DT_EnemyTwoHandWeaponSpec'"));

	TArray<FweaponSpec*> WeaponData;

	Weapon2ListDataTable->GetAllRows<FweaponSpec>(TEXT("GetAllRows"), WeaponData);

	for (int32 i = 0; i < WeaponData.Num(); i++)
	{

		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());

		FString tempString = "W2_";
		tempString += FString::FromInt(i);

		WO->_RowName = FName(tempString);

		WO->WeaponObject1 = *WeaponData[i];

		WO->indexNum = i;

		Weapon2ListView->AddItem(WO);

	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Visible);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	SwitcherUI->SetActiveWidgetIndex(2);

	if (TRGM->enemyREF->GetActorRotation().Yaw != 180.0f) {
		TRGM->RotateEnemy(false);
	}
}

//에너미 특수기능 선택 부분
void UTestRoomSetWidget::ShowEnemyAbilitySettingUI()
{
	AbilityListView->ClearListItems();

	AbilityDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyGearSpec.DT_EnemyGearSpec'"));

	TArray<FgearSpec*> AbilityData;

	AbilityDataTable->GetAllRows<FgearSpec>(TEXT("GetAllRows"), AbilityData);

	for (int32 i = 0; i < AbilityData.Num(); i++)
	{

		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());

		FString tempString;
		tempString = FString::FromInt(i);

		WO->_RowName = FName(tempString);

		WO->AbilityObject = *AbilityData[i];

		WO->indexNum = i;

		AbilityListView->AddItem(WO);

	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Visible);

	SwitcherUI->SetActiveWidgetIndex(3);

	if (TRGM->enemyREF->GetActorRotation().Yaw != 0.0f) {
		TRGM->RotateEnemy(true);
	}
}

void UTestRoomSetWidget::ResetEuqipState(int32 listType, int32 listNum)
{
	TArray<UObject*> listItems;
	switch (listType)
	{
	case 0:
		listItems = EnemyBodyListView->GetListItems();
		for (UObject* item : listItems) {
			UWeapon1Object* bodyItem = Cast<UWeapon1Object>(item);
			if (bodyItem)
			{
				if (bodyItem->indexNum == listNum)
				{
					bodyItem->bIsEquiped = true;
				}
				else {
					bodyItem->bIsEquiped = false;
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("no list?"));
			}
		}
		EnemyBodyListView->RegenerateAllEntries();
		break;
	case 1:
		listItems = Weapon1ListView->GetListItems();
		for (UObject* item : listItems) {
			UWeapon1Object* bodyItem = Cast<UWeapon1Object>(item);
			if (bodyItem)
			{
				if (bodyItem->indexNum == listNum && listNum != 0)
				{
					bodyItem->bIsEquiped = true;
				}
				else {
					bodyItem->bIsEquiped = false;
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("no list?"));
			}
		}
		Weapon1ListView->RegenerateAllEntries();
		break;
	case 2:
		listItems = Weapon2ListView->GetListItems();
		for (UObject* item : listItems) {
			UWeapon1Object* bodyItem = Cast<UWeapon1Object>(item);
			if (bodyItem)
			{
				if (bodyItem->indexNum == listNum && listNum != 0)
				{
					bodyItem->bIsEquiped = true;
				}
				else {
					bodyItem->bIsEquiped = false;
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("no list?"));
			}
		}
		Weapon2ListView->RegenerateAllEntries();
		break;
	case 3:
		listItems = AbilityListView->GetListItems();
		for (UObject* item : listItems) {
			UWeapon1Object* bodyItem = Cast<UWeapon1Object>(item);
			if (bodyItem)
			{
				if (bodyItem->indexNum == listNum && listNum != 0)
				{
					bodyItem->bIsEquiped = true;
				}
				else {
					bodyItem->bIsEquiped = false;
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("no list?"));
			}
		}
		AbilityListView->RegenerateAllEntries();
		break;
	default:
		break;
	}
}

void UTestRoomSetWidget::SetEnemySpec(int32 UISwitch, FName RowName)
{
	if (TRGM) {
		if (TRGM->enemyREF) {
			text_ESTotalHP->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->enemySpec.totalHP)));
			if (TRGM->enemyREF->weapon1) {
				text_ESWeapon1ATK->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->weapon1->weaponStat.damage)));;
			}
			else {
				text_ESWeapon1ATK->SetText(FText::FromString("-"));
			}

			if (TRGM->enemyREF->weapon2) {
				text_ESWeapon2ATK->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->weapon2->weaponStat.damage)));;
			}
			else {
				text_ESWeapon2ATK->SetText(FText::FromString("-"));
			}
			text_ESTotalDEF->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->enemySpec.totalDEF)));
			text_ESSpeed->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), 600 * TRGM->enemyREF->enemySpec.speed)));
			text_ESWeightLimit->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->enemySpec.weightLimit)));
			text_ESCurrentWeight->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->enemySpec.currentWeight)));;
			text_ESTotalCost->SetText(FText::FromString(FString::FromInt(TRGM->enemyREF->enemySpec.totalCost)));;

			if (TRGM->enemyREF->enemySpec.weightLimit < TRGM->enemyREF->enemySpec.currentWeight) {
				text_ESSpeed->SetColorAndOpacity(FColor::Red);
				text_ESWeightLimit->SetColorAndOpacity(FColor::Red);
				text_ESCurrentWeight->SetColorAndOpacity(FColor::Red);
			}
			else {
				text_ESSpeed->SetColorAndOpacity(FColor::White);
				text_ESWeightLimit->SetColorAndOpacity(FColor::White);
				text_ESCurrentWeight->SetColorAndOpacity(FColor::White);
			}

			if (UISwitch != -1) {
				partUISwitcher->SetVisibility(ESlateVisibility::Visible);
			}
			
			switch (UISwitch) {
			case 0:
				partUISwitcher->SetActiveWidgetIndex(0);
				if (gi) {
					FbodySpec* bodyData = gi->DT_BodyData->FindRow<FbodySpec>(RowName, "");

					text_BSHP->SetText(FText::FromString(FString::FromInt(bodyData->HP)));
					text_BSDEF->SetText(FText::FromString(FString::FromInt(bodyData->DEF)));
					text_BSSpeed->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), 600 * bodyData->speed)));
					text_BSWeightLimit->SetText(FText::FromString(FString::FromInt(bodyData->weightLimit)));
					text_BSCost->SetText(FText::FromString(FString::FromInt(bodyData->cost)));
					text_Discription->SetText(FText::FromString(bodyData->discription));
				}
				break;
			case 1:
				partUISwitcher->SetActiveWidgetIndex(1);
				if (gi) {
					FweaponSpec* weaponData = gi->DT_Weapon1Data->FindRow<FweaponSpec>(RowName, "");
					text_WSDamage->SetText(FText::FromString(FString::FromInt(weaponData->damage)));
					text_WSDEF->SetText(FText::FromString(FString::FromInt(weaponData->DEF)));
					text_WSATKRange->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), weaponData->attackRange)));
					text_WSATKCooldown->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), weaponData->attackCooldown)));
					text_WSWeight->SetText(FText::FromString(FString::FromInt(weaponData->weight)));
					text_WSCost->SetText(FText::FromString(FString::FromInt(weaponData->cost)));
					text_Discription->SetText(FText::FromString(weaponData->description));
				}
				break;
			case 2:
				partUISwitcher->SetActiveWidgetIndex(1);
				if (gi) {
					FweaponSpec* weaponData = gi->DT_Weapon2Data->FindRow<FweaponSpec>(RowName, "");
					text_WSDamage->SetText(FText::FromString(FString::FromInt(weaponData->damage)));
					text_WSDEF->SetText(FText::FromString(FString::FromInt(weaponData->DEF)));
					text_WSATKRange->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), weaponData->attackRange)));
					text_WSATKCooldown->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), weaponData->attackCooldown)));
					text_WSWeight->SetText(FText::FromString(FString::FromInt(weaponData->weight)));
					text_WSCost->SetText(FText::FromString(FString::FromInt(weaponData->cost)));
					text_Discription->SetText(FText::FromString(weaponData->description));
				}
				break;
			case 3:
				partUISwitcher->SetActiveWidgetIndex(2);
				if (gi) {
					FgearSpec* gearData = gi->DT_GearData->FindRow<FgearSpec>(RowName, "");
					if (gearData->bIsBuffType) {
						text_GSBuffType->SetText(FText::FromString(L"버프형"));
						text_GSActiveTime->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), gearData->activeTime)));
					}
					else {
						text_GSBuffType->SetText(FText::FromString(L"발사형"));
						text_GSActiveTime->SetText(FText::FromString("-"));
					}
					text_GSCooldown->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), gearData->useCooldown)));
					text_GSWeight->SetText(FText::FromString(FString::FromInt(gearData->weight)));
					text_GSCost->SetText(FText::FromString(FString::FromInt(gearData->cost)));
					text_Discription->SetText(FText::FromString(gearData->discription));
				}
				break;
			default:
				break;
			}
		}
	}
}

// 에너미 설정에 필요한 총 코스트를 실시간으로 표시하기 위한 함수
void UTestRoomSetWidget::UpdateMonsterCost()
{
	TextBlock_MonsterCost->SetText(FText::AsNumber(TRGM->enemyREF->enemySpec.totalCost));
}
