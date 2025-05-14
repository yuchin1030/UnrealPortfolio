// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHR/BaseEnemy.h"
#include "Yuchin/PlayerInfoSaveData.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ListView.h>
#include "EnemyCustomizer.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UEnemyCustomizer : public UUserWidget
{
	GENERATED_BODY()


protected:
	void NativeConstruct() override;



public:
	class ABaseEnemy* CustomEnemy;
	class ACustomModeBase* CM;
	FPlayerInfoSaveDataStruct playerData;
	

	// �÷��̾��� ���� ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Gold;

	int32 CurrentplayerGold = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta =(BindWidget))
	class UWidgetSwitcher* SwitcherUI; // 0: ��ü ����, 1: ���� ���� 2: AI ����

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UWidgetSwitcher* EnemyUISwitcher;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* SettingBtn;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* ReturnBtn;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_Yes;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_No;


	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton*  EnemyBodyUI;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyWeaponUI1;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyWeaponUI2;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* EnemyAbilitySettingUI;



	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> EnemyBodyListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Weapon1ListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Weapon2ListView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> AbilityListView;


	bool Test;
	
	UFUNCTION()
	void SaveComplete();




	// ī�װ� �̹��� (��ư Ŭ�� �� ������ ���� ����� ���ؼ� ����)
	// Ȱ��ȭ �� ��Ÿ���� ī�װ� �̹���
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_Body;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_MainWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_SubWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_On_Ability;

	UPROPERTY(meta = (BindWidget))
	class UImage* System_CreateMon;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* FadeOut;
	//===================================================








private:
	int32 SwitcherIndex = 0;

	UFUNCTION()
	void ClickSettingBtn();
	UFUNCTION()
	void ClickReturnBtn();
	UFUNCTION()
	void ShowEnemyBodyUI();
	UFUNCTION()
	void ShowEnemyWeaponUI1();
	UFUNCTION()
	void ShowEnemyWeaponUI2();
	UFUNCTION()
	void ShowEnemyAbilitySettingUI();

	UFUNCTION()
	void ReturnMap();

	UFUNCTION()
	void CancelReturnMap();

	UPROPERTY()
	UDataTable* Weapon1ListDataTable;
	UPROPERTY()
	UDataTable* Weapon2ListDataTable;
	UPROPERTY()
	UDataTable* EnemyBodyDataTable;
	UPROPERTY()
	UDataTable* AbilityDataTable;

};
