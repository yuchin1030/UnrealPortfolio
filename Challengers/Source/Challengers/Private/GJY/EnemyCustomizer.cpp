// Fill o your copyright notice in the Description page of Project Settings.


#include "GJY/EnemyCustomizer.h"
#include "CHR/BaseEnemy.h"
#include "CHR/EnemyBodyStruct.h"
#include "CHR/WeaponStruct.h"
#include "CHR/GearStruct.h"
#include "GJY/WeaponList1.h"
#include "GJY/Weapon1Object.h"
#include "GJY/CustomModeBase.h"
#include "BJK/MainPlayerWidget.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "EngineUtils.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "OurGameInstance.h"

void UEnemyCustomizer::NativeConstruct()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	EnemyUISwitcher->SetActiveWidgetIndex(0);

	CM = Cast<ACustomModeBase>(GetWorld()->GetAuthGameMode());

	for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		CustomEnemy = *it;
	}

	SettingBtn->OnClicked.AddDynamic(this, &UEnemyCustomizer::ClickSettingBtn);
	ReturnBtn->OnClicked.AddDynamic(this, &UEnemyCustomizer::ClickReturnBtn);


	EnemyBodyUI->OnClicked.AddDynamic(this, &UEnemyCustomizer::ShowEnemyBodyUI);
	EnemyWeaponUI1->OnClicked.AddDynamic(this, &UEnemyCustomizer::ShowEnemyWeaponUI1);
	EnemyWeaponUI2->OnClicked.AddDynamic(this, &UEnemyCustomizer::ShowEnemyWeaponUI2);
	EnemyAbilitySettingUI->OnClicked.AddDynamic(this, &UEnemyCustomizer::ShowEnemyAbilitySettingUI);
	Button_Yes->OnClicked.AddDynamic(this, &UEnemyCustomizer::ReturnMap);
	Button_No->OnClicked.AddDynamic(this, &UEnemyCustomizer::CancelReturnMap);

	SwitcherUI->SetActiveWidgetIndex(0);
	EnemyUISwitcher->SetActiveWidgetIndex(0);

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	System_CreateMon->SetVisibility(ESlateVisibility::Hidden);

	UOurGameInstance* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	gi->LoadPlayerInfoData();

	playerData = gi->loadedPlayerInfoDataList;
			
	UE_LOG(LogTemp, Warning, TEXT("playerName ; %s : %s"), *gi->loadedPlayerInfoDataList.playerName, *gi->playerName);

	CurrentplayerGold = gi->loadedPlayerInfoDataList.playerGold;
	UE_LOG(LogTemp, Warning, TEXT("playerGold ; %d"), CurrentplayerGold);

	gi->SavePlayerInfoData(playerData.playerName, playerData.playerLevel, playerData.playerGold- CurrentplayerGold, playerData.playerCurrentExp, playerData.playerMaxExp, playerData.playerEnemyCost, playerData.weaponLevel, playerData.currentWeaponStat, playerData.nextWeaponStat, playerData.upgWeaponNeedGold);

	// 에너미 코스트
	CustomEnemy->enemySpec.totalCost;
	TextBlock_Gold->SetText(FText::FromString(FString::FromInt(CurrentplayerGold)));
	
}

void UEnemyCustomizer::SaveComplete()
{
	System_CreateMon->SetVisibility(ESlateVisibility::Visible);
	UUserWidget::PlayAnimation(FadeOut, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UEnemyCustomizer::ClickSettingBtn()
{	
	// AI Setting UI를 연다.
	if(CM != nullptr)
	{
		CM->ShowAISettingUI();
	}
	
}

// 마을로 돌아가는 부분.
void UEnemyCustomizer::ClickReturnBtn()
{

	EnemyUISwitcher->SetActiveWidgetIndex(1);
}

//에너미 몸체설정 부분
void UEnemyCustomizer::ShowEnemyBodyUI()
{

	SwitcherUI->SetActiveWidgetIndex(0);
	EnemyBodyListView->ClearListItems();
	
	EnemyBodyDataTable = LoadObject<UDataTable>(nullptr,TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyBodySpec.DT_EnemyBodySpec'"));

	TArray<FbodySpec*> bodyData;

	EnemyBodyDataTable->GetAllRows<FbodySpec>(TEXT("GetAllRows"),bodyData);

	int32 normalNum = 1;
	int32 bossNum = 1;
	for(int32 i = 0; i< bodyData.Num();i++)
	{
		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());
		WO->BodyObject = *bodyData[i];

		FString tempString;


		if(!WO->BodyObject.bIsBossType)
		{
			tempString = "NB";
			tempString+=FString::FromInt(normalNum);
			normalNum++;
		}
		else
		{
			tempString = "BB";
			tempString+=FString::FromInt(bossNum);
			bossNum++;
		}

		WO->_RowName = FName(tempString);

		EnemyBodyListView->AddItem(WO);
	}

	Image_On_Body->SetVisibility(ESlateVisibility::Visible);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	if (CustomEnemy->GetActorRotation().Yaw != 180.0f) {
		CM->RotateEnemy(CustomEnemy, false);
	}
}

//웨폰1번 리스트 선택 부분
void UEnemyCustomizer::ShowEnemyWeaponUI1()
{  

	//WeaponList에 표시되어야 할 목록. 이름: 데미지, 사거리, 쿨다운, 무게, 가격

	SwitcherUI->SetActiveWidgetIndex(1);
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

		Weapon1ListView->AddItem(WO);
	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Visible);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	if (CustomEnemy->GetActorRotation().Yaw != 180.0f) {
		CM->RotateEnemy(CustomEnemy, false);
	}
}
//웨폰 2번 리스트 선택 부분
void UEnemyCustomizer::ShowEnemyWeaponUI2()
{
	SwitcherUI->SetActiveWidgetIndex(2);
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

		Weapon2ListView->AddItem(WO);

	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Visible);
	Image_On_Ability->SetVisibility(ESlateVisibility::Hidden);

	if (CustomEnemy->GetActorRotation().Yaw != 0.0f) {
		CM->RotateEnemy(CustomEnemy, true);
	}
}

//에너미 특수기능 선택 부분
void UEnemyCustomizer::ShowEnemyAbilitySettingUI()
{
	SwitcherUI->SetActiveWidgetIndex(3);
	AbilityListView->ClearListItems();

	AbilityDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CHR/Data/DT_EnemyGearSpec.DT_EnemyGearSpec'"));

	TArray<FgearSpec*> AbilityData;

	AbilityDataTable->GetAllRows<FgearSpec>(TEXT("GetAllRows"), AbilityData);

	for (int32 i = 0; i < AbilityData.Num(); i++)
	{

		UWeapon1Object* WO = NewObject<UWeapon1Object>(this, UWeapon1Object::StaticClass());

		FString tempStirng;
		tempStirng = FString::FromInt(i);

		WO->_RowName = FName(tempStirng);

		WO->AbilityObject = *AbilityData[i];
	
		AbilityListView->AddItem(WO);

	}

	Image_On_Body->SetVisibility(ESlateVisibility::Hidden);
	Image_On_MainWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_SubWeapon->SetVisibility(ESlateVisibility::Hidden);
	Image_On_Ability->SetVisibility(ESlateVisibility::Visible);

	if (CustomEnemy->GetActorRotation().Yaw != 180.0f) {
		CM->RotateEnemy(CustomEnemy, false);
	}
}

void UEnemyCustomizer::ReturnMap()
{
	// 로딩 창 띄우기
	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	gi->bSLoading = true;
	
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		pc->SetInputMode(FInputModeGameOnly());
	}
	UGameplayStatics::OpenLevel(GetWorld(), "SingleMap");
}

void UEnemyCustomizer::CancelReturnMap()
{
	EnemyUISwitcher->SetActiveWidgetIndex(0);



}


