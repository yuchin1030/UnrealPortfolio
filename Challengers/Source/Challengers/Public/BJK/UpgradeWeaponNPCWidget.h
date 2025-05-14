#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWeaponNPCWidget.generated.h"

UCLASS()
class CHALLENGERS_API UUpgradeWeaponNPCWidget : public UUserWidget
{
	GENERATED_BODY()
	

	public:

	virtual void NativeConstruct() override;

	class AChallengersCharacter* player;

	class UOurGameInstance* gi;

	bool bClosed;

	// NPC 목소리
	UFUNCTION()
    void UpgreadeWeaponNPCSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* NPCSoundPlay;

	// Panel 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_UpgradeWeapon;


	// 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SelectUpgrade_Weapon;

	// 현재 스위쳐 창 인덱스
	int32 currentSwitcherIndex = 0;

	// 창닫기 =======================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	// =============================================





	// 강화 할 무기 선택 =============================
	// 칼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Sword;

	UFUNCTION()
	void OnClickSelectWeapon_Sword();


	// 지팡이
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Wand;

	UFUNCTION()
	void OnClickSelectWeapon_Wand();


	// 활
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Bow;

	UFUNCTION()
	void OnClickSelectWeapon_Bow();
	// =============================================






	// 강화하기 버튼 누르기 =============================
	
	// 강화 알림 문구 띄어주는 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_bUpgrade;


	// 칼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_OpenSystem_sword;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Upgrade_Sword;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Sword_Close;

	UFUNCTION()
	void OnClickOpenSystem_sword();

	UFUNCTION()
	void OnClickUpgrade_Sword();

	UFUNCTION()
	void OnClickButton_Sword_Close();


	// 지팡이
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_OpenSystem_wand;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Upgrade_Wand;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Wand_Close;

	UFUNCTION()
	void OnClickOpenSystem_wand();

	UFUNCTION()
	void OnClickUpgrade_Wand();

	UFUNCTION()
	void OnClickButton_Wand_Close();


	// 활
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_OpenSystem_bow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Upgrade_Bow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Bow_Close;

	UFUNCTION()
	void OnClickOpenSystem_bow();

	UFUNCTION()
	void OnClickUpgrade_Bow();

	UFUNCTION()
	void OnClickButton_Bow_Close();

	// =============================================







	// 현재 무기 레벨 =============================
	
	// 칼의 현재 레벨
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Sword;

	// 지팡이의 현재 레벨
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Wand;

	// 활의 현재 레벨
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Bow;


	// =============================================





	// 현재 무기 공격력 =============================
	
	// 칼의 현재 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Sword;

	// 지팡이의 현재 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Wand;

	// 활의 현재 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Bow;

	// =============================================





	// 강화 후 무기 공격력 =============================

	// 칼의 강화 후 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Sword;

	// 지팡이의 강화 후 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Wand;

	// 활의 강화 후 공격력
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Bow;


	// =============================================







	// 강화에 필요한 골드량 =============================

	// 칼의 강화에 필요한 골드량
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Sword;

	// 지팡이의 강화에 필요한 골드량
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Wand;

	// 활의 강화에 필요한 골드량
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Bow;

	// =============================================


};
