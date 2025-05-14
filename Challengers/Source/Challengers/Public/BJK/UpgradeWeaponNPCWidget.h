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

	// NPC ��Ҹ�
	UFUNCTION()
    void UpgreadeWeaponNPCSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* NPCSoundPlay;

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_UpgradeWeapon;


	// ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SelectUpgrade_Weapon;

	// ���� ������ â �ε���
	int32 currentSwitcherIndex = 0;

	// â�ݱ� =======================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnClickClose();
	// =============================================





	// ��ȭ �� ���� ���� =============================
	// Į
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Sword;

	UFUNCTION()
	void OnClickSelectWeapon_Sword();


	// ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Wand;

	UFUNCTION()
	void OnClickSelectWeapon_Wand();


	// Ȱ
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SelectWeapon_Bow;

	UFUNCTION()
	void OnClickSelectWeapon_Bow();
	// =============================================






	// ��ȭ�ϱ� ��ư ������ =============================
	
	// ��ȭ �˸� ���� ����ִ� ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_bUpgrade;


	// Į
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


	// ������
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


	// Ȱ
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







	// ���� ���� ���� =============================
	
	// Į�� ���� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Sword;

	// �������� ���� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Wand;

	// Ȱ�� ���� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Level_Bow;


	// =============================================





	// ���� ���� ���ݷ� =============================
	
	// Į�� ���� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Sword;

	// �������� ���� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Wand;

	// Ȱ�� ���� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_CunrrentStat_Bow;

	// =============================================





	// ��ȭ �� ���� ���ݷ� =============================

	// Į�� ��ȭ �� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Sword;

	// �������� ��ȭ �� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Wand;

	// Ȱ�� ��ȭ �� ���ݷ�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NextStat_Bow;


	// =============================================







	// ��ȭ�� �ʿ��� ��差 =============================

	// Į�� ��ȭ�� �ʿ��� ��差
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Sword;

	// �������� ��ȭ�� �ʿ��� ��差
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Wand;

	// Ȱ�� ��ȭ�� �ʿ��� ��差
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_NeedMoney_Bow;

	// =============================================


};
