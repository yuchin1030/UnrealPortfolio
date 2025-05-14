// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UMainPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	class AChallengersCharacter* player;

	class UOurGameInstance* OG;

	// ���ⱳü ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_MainPlayer;

	// ��ų ������ ��ü ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SkillIcon;

	// ���� ��ü ������
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_BuffDeBuff;

	UFUNCTION()
	void ShowBuff(int32 BuffNum);

	UFUNCTION()
	void HiddenBuff();

	// ��ȣ�ۿ� �̹���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Interaction;

	// ���� ���� �� �߻��ϴ� �ִϸ��̼�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ChangeWeaponAnim;

	UFUNCTION()
	void ChangeAnim();



	UPROPERTY(EditDefaultsOnly, Category = "BuffSound")
	class USoundBase* BuffSound;

	UPROPERTY(EditDefaultsOnly, Category = "BuffSound")
	class USoundBase* DeBuffSound;



	// ���� �ð�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_BlockTime;


	UPROPERTY(EditAnywhere,  Category = "BuffDebuff")
	class ABuffDebuffManager* BuffDebuffManagers;




	// ���� Ŀ���͸���¡ �Ϸ� ����==================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* System_CreateMon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* System_CreateM;

	UFUNCTION()
	void ShowSystemM();

	bool bShowSystemM = false;
	//===============================================




	// ���� ��ü �� ���� �� ����=======================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Red;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Yellow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Green;
	//===============================================





	// ��ų ��Ÿ�� ������====================================
	// [Į]
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Sword_1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Sword_2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Sword_3;

	/*UFUNCTION()
	void CoolTime_Skill_Sword1(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Sword2(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Sword3(float CoolTime);*/




	// [������]
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Wand_1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Wand_2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Wand_3;

	/*UFUNCTION()
	void CoolTime_Skill_Wand1(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Wand2(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Wand3(float CoolTime);*/

	UFUNCTION()
	void CoolTime_Skill(int32 index, float CoolTime);


	// [Ȱ]
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Bow_1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Bow_2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Skill_Bow_3;

	/*UFUNCTION()
	void CoolTime_Skill_Bow1(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Bow2(float CoolTime);

	UFUNCTION()
	void CoolTime_Skill_Bow3(float CoolTime);*/


	//===============================================




	// ä�� ���� / �ݱ� ��ư========================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Chat;

	UFUNCTION()
	void OnClickChat();

	// ���� �ݱ� �������
	int Num =1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* CloseChat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* OpenChat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Chat_Close;

	//===============================================







	// �ؽ��� ���� ===================================
	int32 CurrentCoin;
	// ���� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Coin;

	// ���� ���
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Coin;

	// ���Ҹ� �Ǿ����� �Ǻ��ϴ� ���
	UFUNCTION()
    void SpendCoin();

	int32 PlayerLevel;
	// ���� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerLevel;
	//===============================================








	//[������]====================================
	// �÷��̾� HP
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* Player_HPBar;

	UFUNCTION()
	void HP_Update(float HP);



	// �÷��̾� MP
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* Player_MPBar;

	UFUNCTION(BlueprintCallable)
	void MP_Update(float MP);
	


	// �÷��̾� ����ġ ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_EXPBar;


	UFUNCTION()
	void EXP_Update(class AChallengersCharacter* target);
	//===============================================











	// �ִϸ��̼�======================================
	// Į ���� �� ���� �ִϸ��̼�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectSword;

	// �ش� ���� ȸ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotSword;

	UFUNCTION()
	void AnimSword(int32 WeaponNum);



	// ������ ���� �� ���� �ִϸ��̼�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectWand;

	// �ش� ���� ȸ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotWand;

	UFUNCTION()
	void AnimWand(int32 WeaponNum);



	// Ȱ ���� �� ���� �ִϸ��̼�
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectBow;

	// �ش� ���� ȸ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotBow;

	UFUNCTION()
	void AnimBow(int32 WeaponNum);


	//===============================================





	//[��� UI]======================================
	// �ɼ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Option;

	UFUNCTION()
	void OnClickOptionButton();

	// ��ų ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_SKill;

	UFUNCTION()
	void OnClickSkillButton();
	//===============================================

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	int32 weaponNum = 5;

	UFUNCTION()
	void ChangeSwitcher();

	//===============================================
	// ä��

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UChatWidget> chatUI_BP;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableText* Editable_chat;	

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* ScrollBox_chat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UBorder* Border_Chat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UVerticalBox* vertical_chat;

	
	UFUNCTION()
	void OnMySendMsg();

	UFUNCTION()
	void AddMsg(const FString& msg);

	UFUNCTION()
	void ActiveEditableChat();

	UFUNCTION()
	void DeActiveEditableChat(const FText& Text, ETextCommit::Type CommitMethod);

};
