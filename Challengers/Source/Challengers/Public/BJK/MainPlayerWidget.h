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

	// 무기교체 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_MainPlayer;

	// 스킬 아이콘 교체 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_SkillIcon;

	// 버프 교체 스위쳐
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_BuffDeBuff;

	UFUNCTION()
	void ShowBuff(int32 BuffNum);

	UFUNCTION()
	void HiddenBuff();

	// 상호작용 이미지
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Interaction;

	// 무기 변경 시 발생하는 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ChangeWeaponAnim;

	UFUNCTION()
	void ChangeAnim();



	UPROPERTY(EditDefaultsOnly, Category = "BuffSound")
	class USoundBase* BuffSound;

	UPROPERTY(EditDefaultsOnly, Category = "BuffSound")
	class USoundBase* DeBuffSound;



	// 버프 시간
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_BlockTime;


	UPROPERTY(EditAnywhere,  Category = "BuffDebuff")
	class ABuffDebuffManager* BuffDebuffManagers;




	// 몬스터 커스터마이징 완료 문구==================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* System_CreateMon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* System_CreateM;

	UFUNCTION()
	void ShowSystemM();

	bool bShowSystemM = false;
	//===============================================




	// 무기 교체 시 슬롯 색 변경=======================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Red;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Yellow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Green;
	//===============================================





	// 스킬 쿨타임 게이지====================================
	// [칼]
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




	// [지팡이]
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


	// [활]
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




	// 채팅 열기 / 닫기 버튼========================================
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Chat;

	UFUNCTION()
	void OnClickChat();

	// 열기 닫기 순서대로
	int Num =1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* CloseChat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* OpenChat;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Chat_Close;

	//===============================================







	// 텍스쳐 연결 ===================================
	int32 CurrentCoin;
	// 현재 골드
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Coin;

	// 현재 골드
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Coin;

	// 골드소모가 되었는지 판별하는 기능
	UFUNCTION()
    void SpendCoin();

	int32 PlayerLevel;
	// 현재 레벨
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerLevel;
	//===============================================








	//[프로필]====================================
	// 플레이어 HP
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* Player_HPBar;

	UFUNCTION()
	void HP_Update(float HP);



	// 플레이어 MP
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* Player_MPBar;

	UFUNCTION(BlueprintCallable)
	void MP_Update(float MP);
	


	// 플레이어 경험치 바
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_EXPBar;


	UFUNCTION()
	void EXP_Update(class AChallengersCharacter* target);
	//===============================================











	// 애니메이션======================================
	// 칼 선택 시 최초 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectSword;

	// 해당 무기 회전
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotSword;

	UFUNCTION()
	void AnimSword(int32 WeaponNum);



	// 지팡이 선택 시 최초 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectWand;

	// 해당 무기 회전
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotWand;

	UFUNCTION()
	void AnimWand(int32 WeaponNum);



	// 활 선택 시 최초 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimSelectBow;

	// 해당 무기 회전
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* RotBow;

	UFUNCTION()
	void AnimBow(int32 WeaponNum);


	//===============================================





	//[기능 UI]======================================
	// 옵션 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Option;

	UFUNCTION()
	void OnClickOptionButton();

	// 스킬 버튼
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
	// 채팅

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
