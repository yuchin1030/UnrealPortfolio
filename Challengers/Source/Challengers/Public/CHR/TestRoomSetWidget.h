// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestRoomSetWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTestRoomSetWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta =(BindWidget))
	class UWidgetSwitcher* SwitcherUI; // 0: 몸체 설정, 1: 무기 설정 2: AI 설정

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UWidgetSwitcher* partUISwitcher;// 0: 몸체 설정, 1: 무기 설정 2: AI 설정

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* SettingBtn;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* ReturnBtn;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton*  EnemyBodyUI;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyWeaponUI1;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyWeaponUI2;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyAbilitySettingUI;
	// 도움말 열기 버튼
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* btn_Question;
	// 도움말 닫기 버튼
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_HelpClose;

	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> EnemyBodyListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> Weapon1ListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> Weapon2ListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> AbilityListView;

	
	// 카테고리 이미지 (버튼 클릭 시 생성과 숨김 기능을 위해서 만듦)
	// 활성화 시 나타나는 카테고리 이미지
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_Body;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_MainWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_SubWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_Ability;

	// 도움말 뒷 배경
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_HelpBackGround;

	// 도움말 보더
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_Help;

	// 플레이어의 현재 소지금 표시
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_playerGold;

	// 유저가 설정한 몬스터의 총 가격 표시
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_MonsterCost;

	//에너미, 파츠정보 텍스트 리스트 시작
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESTotalHP;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESWeapon1ATK;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESWeapon2ATK;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESTotalDEF;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESWeightLimit;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESCurrentWeight;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_ESTotalCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_BSHP;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_BSDEF;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_BSSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_BSWeightLimit;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_BSCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSDamage;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSDEF;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSATKRange;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSATKCooldown;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSWeight;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_WSCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_GSBuffType;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_GSActiveTime;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_GSCooldown;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_GSWeight;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_GSCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_Discription;

	// 리스트 끝

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* showSaveComplete;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* canNotSelect;

	class ATestRoomGameMode* TRGM = nullptr;

	class AMainPlayerController* pc = nullptr;

	class ACameraActor* settingCamera = nullptr;

	class AChallengersCharacter* player = nullptr;

	class UOurGameInstance* gi = nullptr;

	UPROPERTY()
	FName bodyRowName = FName("NB1");//몸체의 RowName

	UPROPERTY()
	FName weapon1RowName = FName("W1_0");//장비1의 RowName

	UPROPERTY()
	FName weapon2RowName = FName("W2_0");//장비2의 RowName

	UPROPERTY()
	FName gearRowName = FName("0");//특수능력의 RowName

	void Init(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName);

	// 에너미 설정에 필요한 총 코스트를 실시간으로 표시하기 위한 함수
	UFUNCTION()
	void UpdateMonsterCost();

	void SetEnemySpec(int32 UISwitch, FName RowName);

	UFUNCTION()
	void ShowEnemyBodyUI();
	UFUNCTION()
	void ShowEnemyWeaponUI1();
	UFUNCTION()
	void ShowEnemyWeaponUI2();
	UFUNCTION()
	void ShowEnemyAbilitySettingUI();

	void ResetEuqipState(int32 listType, int32 listNum);

private:
	UPROPERTY()
	UDataTable* Weapon1ListDataTable;
	UPROPERTY()
	UDataTable* Weapon2ListDataTable;
	UPROPERTY()
	UDataTable* EnemyBodyDataTable;
	UPROPERTY()
	UDataTable* AbilityDataTable;

	UFUNCTION()
	void ClickSettingBtn();
	UFUNCTION()
	void ClickReturnBtn();
	UFUNCTION()
	void ClickOpenHelpBtn();
	UFUNCTION()
	void ClickCloseHelpBtn();
};
