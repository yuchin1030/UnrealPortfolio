// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API USkillSettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	class AChallengersCharacter* player;

	UPROPERTY()
	FString playerName = " ";

	// Panel 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_SKillSetting;


	// 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SkillSetWeapon;

	// 게이지 이펙트 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_EF;


	// 텍스트 설정 ====================================
	// 현재 스킬 포인트
	int32 CurrentSkillPoint;

	// 각 장비의 현재 레벨
	int32 Sword1;
	int32 Sword2;
	int32 Sword3;
	int32 Wand1;
	int32 Wand2;
	int32 Wand3;
	int32 Bow1;
	int32 Bow2;
	int32 Bow3;

	// 스킬 포인트 (현재 플레이어가 가지고 있는 포인트 갯수)
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SkillPoint;


	// 칼 강화 레벨
	// 칼 스킬 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_1;

	

	// 칼 스킬 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_2;

	// 칼 스킬 3
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_3;




	// 지팡이 강화 레벨
	// 지팡이 스킬 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_1;

	// 지팡이 스킬 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_2;

	// 지팡이 스킬 3
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_3;




	// 활 강화 레벨
	// 활 스킬 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_1;

	// 활 스킬 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_2;

	// 활 스킬 3

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_3;

	

	// =============================================

	// 애니메이션 재생================================
	// 칼 아이콘 선택 시 애니메이션 재생
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectSwordIcon;

	// 지팡이 아이콘 선택 시 애니메이션 재생
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectWandIcon;

	// 활 아이콘 선택 시 애니메이션 재생
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectBowIcon;


	int Num = 1;


	// 프리셋 열기 애니메이션 재생
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* OpenPreSet;

	// 프리셋 닫기 애니메이션 재생
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ClosePreSet;

	// =============================================




	// 창닫기 =======================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	// =============================================




	// 프리셋 버튼 ===================================
	//열기
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Preset;

	UFUNCTION()
	void OnClickPreset();

	// 1번 프리셋
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Set_Preset_1;

	UFUNCTION()
	void OnClickSetPreset_1();

	// 2번 프리셋
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Set_Preset_2;

	UFUNCTION()
	void OnClickSetPreset_2();
	// =============================================





	// 스킬 정보 저장 ================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SaveSkill;

	UFUNCTION()
	void OnClickSkillSave();
	// =============================================




	// 스킬 초기화 ================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_ResetAllSkill;

	UFUNCTION()
	void OnClickResetAllSkill();

	// =============================================





	// 메인 무기들의 아이콘=============================
	// 스킬셋 칼 아이콘
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MainIcon_Sword;

	UFUNCTION()
	void OnClickMainIconSword();

	// 스킬셋 지팡이 아이콘
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MainIcon_Wand;

	UFUNCTION()
	void OnClickMainIconWand();

	// 스킬셋 활 아이콘
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MainIcon_Bow;

	UFUNCTION()
	void OnClickMainIconBow();



	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Main_Sword;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Main_Wand;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Main_Bow;

	// =============================================






	// [칼]
	// 칼의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SwordSkill_1;

	UFUNCTION()
	void OnHoveredSwordSkill_1();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SwordSkill_2;

	UFUNCTION()
	void OnHoveredSwordSkill_2();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SwordSkill_3;

	UFUNCTION()
	void OnHoveredSwordSkill_3();

	// 칼의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite , meta = (BindWidget))
	class UButton* Button_SwordSkill_1_Upgrade;

	UFUNCTION()
	void OnClickSwordSkill_1_Upgrade();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_SwordSkill_2_Upgrade;

	UFUNCTION()
	void OnClickSwordSkill_2_Upgrade();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_SwordSkill_3_Upgrade;

	UFUNCTION()
	void OnClickSwordSkill_3_Upgrade();

	// =============================================






	// [지팡이]
	// 지팡이의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_WandSkill_1;
	
	UFUNCTION()
	void OnHoveredWandSkill_1();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_WandSkill_2;

	UFUNCTION()
	void OnHoveredWandSkill_2();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_WandSkill_3;

	UFUNCTION()
	void OnHoveredWandSkill_3();

	// 지팡이의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_WandSkill_1_Upgrade;

	UFUNCTION()
	void OnClickWandSkill_1_Upgrade();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_WandSkill_2_Upgrade;

	UFUNCTION()
	void OnClickWandSkill_2_Upgrade();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_WandSkill_3_Upgrade;

	UFUNCTION()
	void OnClickWandSkill_3_Upgrade();

	// =============================================







	// [활]
	// 활의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_BowSkill_1;

	UFUNCTION()
	void OnHoveredBowSkill_1();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_BowSkill_2;

	UFUNCTION()
	void OnHoveredBowSkill_2();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_BowSkill_3;

	UFUNCTION()
	void OnHoveredBowSkill_3();



	// 활의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_BowSkill_1_Upgrade;

	UFUNCTION()
	void OnClickBowSkill_1_Upgrade();



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_BowSkill_2_Upgrade;

	UFUNCTION()
	void OnClickBowSkill_2_Upgrade();



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_BowSkill_3_Upgrade;

	UFUNCTION()
	void OnClickBowSkill_3_Upgrade();

	// =============================================

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY()
	TArray<int32> skillLevel;

	UFUNCTION()
	void SetSkillLevel();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Text_Level;

	FText SkillLevelPoint;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Text_CurrentDmg;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* Text_NextDmg;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* SkillNameSwitcher;


	int32 SkillPointIndex = 0;
	float Damage = 0;
	float NextDamage = 0;

	float SwordWeaponDmg = 0;
	float StaffWeaponDmg = 0;
	float BowWeaponDmg = 0;

	FString SkillLevelPointString;
	int SkillLevelPointInt;

	FString DamageStirng;
	FString NextDamageString;
	FText DamageText;
	FText NextDamageText;

	UPROPERTY()
	UDataTable* SDT;
};
