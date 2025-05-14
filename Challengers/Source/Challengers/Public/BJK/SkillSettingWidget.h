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

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_SKillSetting;


	// ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SkillSetWeapon;

	// ������ ����Ʈ ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_EF;


	// �ؽ�Ʈ ���� ====================================
	// ���� ��ų ����Ʈ
	int32 CurrentSkillPoint;

	// �� ����� ���� ����
	int32 Sword1;
	int32 Sword2;
	int32 Sword3;
	int32 Wand1;
	int32 Wand2;
	int32 Wand3;
	int32 Bow1;
	int32 Bow2;
	int32 Bow3;

	// ��ų ����Ʈ (���� �÷��̾ ������ �ִ� ����Ʈ ����)
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SkillPoint;


	// Į ��ȭ ����
	// Į ��ų 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_1;

	

	// Į ��ų 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_2;

	// Į ��ų 3
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Sword_3;




	// ������ ��ȭ ����
	// ������ ��ų 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_1;

	// ������ ��ų 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_2;

	// ������ ��ų 3
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Wand_3;




	// Ȱ ��ȭ ����
	// Ȱ ��ų 1
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_1;

	// Ȱ ��ų 2
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_2;

	// Ȱ ��ų 3

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_SL_Bow_3;

	

	// =============================================

	// �ִϸ��̼� ���================================
	// Į ������ ���� �� �ִϸ��̼� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectSwordIcon;

	// ������ ������ ���� �� �ִϸ��̼� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectWandIcon;

	// Ȱ ������ ���� �� �ִϸ��̼� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectBowIcon;


	int Num = 1;


	// ������ ���� �ִϸ��̼� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* OpenPreSet;

	// ������ �ݱ� �ִϸ��̼� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ClosePreSet;

	// =============================================




	// â�ݱ� =======================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	// =============================================




	// ������ ��ư ===================================
	//����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Preset;

	UFUNCTION()
	void OnClickPreset();

	// 1�� ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Set_Preset_1;

	UFUNCTION()
	void OnClickSetPreset_1();

	// 2�� ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Set_Preset_2;

	UFUNCTION()
	void OnClickSetPreset_2();
	// =============================================





	// ��ų ���� ���� ================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SaveSkill;

	UFUNCTION()
	void OnClickSkillSave();
	// =============================================




	// ��ų �ʱ�ȭ ================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_ResetAllSkill;

	UFUNCTION()
	void OnClickResetAllSkill();

	// =============================================





	// ���� ������� ������=============================
	// ��ų�� Į ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MainIcon_Sword;

	UFUNCTION()
	void OnClickMainIconSword();

	// ��ų�� ������ ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MainIcon_Wand;

	UFUNCTION()
	void OnClickMainIconWand();

	// ��ų�� Ȱ ������
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






	// [Į]
	// Į�� 1, 2, 3�� ��ų (���콺�� ���� �ø��� �� ��ų�� ���� ������ ���´�)
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

	// Į�� 1, 2, 3�� ��ų�� ���׷��̵� �� ���ִ� ��ư
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






	// [������]
	// �������� 1, 2, 3�� ��ų (���콺�� ���� �ø��� �� ��ų�� ���� ������ ���´�)
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

	// �������� 1, 2, 3�� ��ų�� ���׷��̵� �� ���ִ� ��ư
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







	// [Ȱ]
	// Ȱ�� 1, 2, 3�� ��ų (���콺�� ���� �ø��� �� ��ų�� ���� ������ ���´�)
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



	// Ȱ�� 1, 2, 3�� ��ų�� ���׷��̵� �� ���ִ� ��ư
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
