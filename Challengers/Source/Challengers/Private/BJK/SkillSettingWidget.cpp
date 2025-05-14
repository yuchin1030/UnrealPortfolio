
#include "BJK/SkillSettingWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "OurGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
void USkillSettingWidget::NativeConstruct()
{

	SDT = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Yuchin/Skills/DT_SkillsInfo.DT_SkillsInfo'"));

	// 스위쳐
	WidgetSwitcher_SkillSetWeapon->SetActiveWidgetIndex(0);


	// 창닫기
	Button_Close->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickClose);

	// 스킬 초기화
	Button_ResetAllSkill->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickResetAllSkill);

	// 프리셋 창열기 버튼
	Button_Preset->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickPreset);
	Button_Set_Preset_1->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSetPreset_1);
	Button_Set_Preset_2->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSetPreset_2);
	

	// 메인무기 아이콘 (클릭 시 스위쳐 인덱스 변경)
	Button_MainIcon_Sword->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickMainIconSword);
	Button_MainIcon_Wand->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickMainIconWand);
	Button_MainIcon_Bow->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickMainIconBow);

	// 저장
	Button_SaveSkill->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSkillSave);

	CurrentSkillPoint = 30;
	Sword1=0;
	Sword2 = 0;
	Sword3 = 0;
	Wand1 = 0;
	Wand2 = 0;
	Wand3 = 0;
	Bow1 = 0;
	Bow2 = 0;
	Bow3 = 0;


	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));


	TextBlock_SL_Sword_1-> SetText(FText::AsNumber(Sword1));
	TextBlock_SL_Sword_2-> SetText(FText::AsNumber(Sword2));
	TextBlock_SL_Sword_3-> SetText(FText::AsNumber(Sword3));
	TextBlock_SL_Wand_1-> SetText(FText::AsNumber(Wand1));
	TextBlock_SL_Wand_2-> SetText(FText::AsNumber(Wand2));
	TextBlock_SL_Wand_3-> SetText(FText::AsNumber(Wand3));
	TextBlock_SL_Bow_1-> SetText(FText::AsNumber(Bow1));
	TextBlock_SL_Bow_2-> SetText(FText::AsNumber(Bow2));
	TextBlock_SL_Bow_3-> SetText(FText::AsNumber(Bow3));


	// [칼]=================================================================================================
	// 칼 스킬 3개 (마우스 올려놓으면 설명 나옴)
	Button_SwordSkill_1->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredSwordSkill_1);
	Button_SwordSkill_2->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredSwordSkill_2);
	Button_SwordSkill_3->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredSwordSkill_3);
	// 칼 스킬 업그레이드
	Button_SwordSkill_1_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSwordSkill_1_Upgrade);
	Button_SwordSkill_2_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSwordSkill_2_Upgrade);
	Button_SwordSkill_3_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickSwordSkill_3_Upgrade);


	// [지팡이]=================================================================================================
	// 지팡이 스킬 3개 (마우스 올려놓으면 설명 나옴)
	Button_WandSkill_1->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredWandSkill_1);
	Button_WandSkill_2->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredWandSkill_2);
	Button_WandSkill_3->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredWandSkill_3);
	// 지팡이 스킬 업그레이드
	Button_WandSkill_1_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickWandSkill_1_Upgrade);
	Button_WandSkill_2_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickWandSkill_2_Upgrade);
	Button_WandSkill_3_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickWandSkill_3_Upgrade);


	// [활]=================================================================================================
	// 활 스킬 3개 (마우스 올려놓으면 설명 나옴)
	Button_BowSkill_1->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredBowSkill_1);
	Button_BowSkill_2->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredBowSkill_2);
	Button_BowSkill_3->OnClicked.AddDynamic(this, &USkillSettingWidget::OnHoveredBowSkill_3);
	// 활 스킬 업그레이드
	Button_BowSkill_1_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickBowSkill_1_Upgrade);
	Button_BowSkill_2_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickBowSkill_2_Upgrade);
	Button_BowSkill_3_Upgrade->OnClicked.AddDynamic(this, &USkillSettingWidget::OnClickBowSkill_3_Upgrade);

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	skillLevel.Init(0, 9);

	// 0:칼 1:지팡이 2:활
	SwordWeaponDmg = player -> currentWeaponStat[0];
	StaffWeaponDmg = player -> currentWeaponStat[1];
	BowWeaponDmg = player -> currentWeaponStat[2];

	OnHoveredSwordSkill_1();
	UUserWidget::PlayAnimation(SelectSwordIcon, 0, 0, EUMGSequencePlayMode::Forward, 1);
	Image_Main_Sword->SetVisibility(ESlateVisibility::Hidden);

	WidgetSwitcher_EF->SetActiveWidgetIndex(3);



}


// 창닫기
void USkillSettingWidget::OnClickClose()
{
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	SetVisibility(ESlateVisibility::Hidden);
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	player->bShowSkillSet = true;
	Num =2;
}

void USkillSettingWidget::OnClickPreset()
{
	
	Num++;
	if (Num %2 == 0)
	{
		UUserWidget::PlayAnimation(OpenPreSet, 0, 1, EUMGSequencePlayMode::Forward, 1);
		
	}
	if (Num %2 != 0)
	{
		UUserWidget::PlayAnimation(ClosePreSet, 0, 1, EUMGSequencePlayMode::Forward, 1);

	}

}


// 1, 2번 프리셋 버튼==========================
void USkillSettingWidget::OnClickSetPreset_1()
{
	
}

void USkillSettingWidget::OnClickSetPreset_2()
{
	
}
// =============================================


// 스킬 정보 저장
void USkillSettingWidget::OnClickSkillSave()
{
	skillLevel[0] = Sword1;
	skillLevel[1] = Sword2;
	skillLevel[2] = Sword3;
	skillLevel[3] = Wand1;
	skillLevel[4] = Wand2;
	skillLevel[5] = Wand3;
	skillLevel[6] = Bow1;
	skillLevel[7] = Bow2;
	skillLevel[8] = Bow3;

	gi->SaveSkillPresetData(player->playerName, skillLevel, CurrentSkillPoint);

	for (int j = 0; j < 9; j++)
	{
		UE_LOG(LogTemp, Warning, TEXT("skillLevel : %d"), skillLevel[j]);
	}

	UE_LOG(LogTemp, Warning, TEXT("SaveSkill"));

	player->LoadSkillPoints();
}



// 스킬 초기화 (모든 무기 포인트 초기화)
void USkillSettingWidget::OnClickResetAllSkill()
{
	CurrentSkillPoint = 30;
	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));

	Sword1 = 0;
	Sword2 = 0;
	Sword3 = 0;
	Wand1 = 0;
	Wand2 = 0;
	Wand3 = 0;
	Bow1 = 0;
	Bow2 = 0;
	Bow3 = 0;

	TextBlock_SL_Sword_1->SetText(FText::AsNumber(Sword1));
	TextBlock_SL_Sword_2->SetText(FText::AsNumber(Sword2));
	TextBlock_SL_Sword_3->SetText(FText::AsNumber(Sword3));
	TextBlock_SL_Wand_1->SetText(FText::AsNumber(Wand1));
	TextBlock_SL_Wand_2->SetText(FText::AsNumber(Wand2));
	TextBlock_SL_Wand_3->SetText(FText::AsNumber(Wand3));
	TextBlock_SL_Bow_1->SetText(FText::AsNumber(Bow1));
	TextBlock_SL_Bow_2->SetText(FText::AsNumber(Bow2));
	TextBlock_SL_Bow_3->SetText(FText::AsNumber(Bow3));

	UE_LOG(LogTemp, Warning, TEXT("ResetAllSkill"));

}




// 메인 무기들의 아이콘=============================
// 스킬셋 칼 아이콘
void USkillSettingWidget::OnClickMainIconSword()
{
	UE_LOG(LogTemp,Warning,TEXT("MainWeapon_Sword"));
	WidgetSwitcher_SkillSetWeapon->SetActiveWidgetIndex(0);

	UUserWidget::PlayAnimation(SelectSwordIcon,0,0,EUMGSequencePlayMode::Forward,1);
	UUserWidget::StopAnimation(SelectWandIcon);
	UUserWidget::StopAnimation(SelectBowIcon);

	Image_Main_Sword->SetVisibility(ESlateVisibility::Hidden);
	Image_Main_Wand->SetVisibility(ESlateVisibility::Visible);
	Image_Main_Bow->SetVisibility(ESlateVisibility::Visible);

	OnHoveredSwordSkill_1();

	WidgetSwitcher_EF->SetActiveWidgetIndex(3);
}

// 스킬셋 지팡이 아이콘
void USkillSettingWidget::OnClickMainIconWand()
{
	UE_LOG(LogTemp, Warning, TEXT("MainWeapon_Orb"));
	WidgetSwitcher_SkillSetWeapon->SetActiveWidgetIndex(1);

	UUserWidget::PlayAnimation(SelectWandIcon, 0, 0, EUMGSequencePlayMode::Forward, 1);
	UUserWidget::StopAnimation(SelectSwordIcon);
	UUserWidget::StopAnimation(SelectBowIcon);

	Image_Main_Sword->SetVisibility(ESlateVisibility::Visible);
	Image_Main_Wand->SetVisibility(ESlateVisibility::Hidden);
	Image_Main_Bow->SetVisibility(ESlateVisibility::Visible);

	OnHoveredWandSkill_1();

	WidgetSwitcher_EF->SetActiveWidgetIndex(3);
}

// 스킬셋 활 아이콘
void USkillSettingWidget::OnClickMainIconBow()
{
	UE_LOG(LogTemp, Warning, TEXT("MainWeapon_Bow"));
	WidgetSwitcher_SkillSetWeapon->SetActiveWidgetIndex(2);

	UUserWidget::PlayAnimation(SelectBowIcon, 0, 0, EUMGSequencePlayMode::Forward, 1);
	UUserWidget::StopAnimation(SelectWandIcon);
	UUserWidget::StopAnimation(SelectSwordIcon);

	Image_Main_Sword->SetVisibility(ESlateVisibility::Visible);
	Image_Main_Wand->SetVisibility(ESlateVisibility::Visible);
	Image_Main_Bow->SetVisibility(ESlateVisibility::Hidden);

	OnHoveredBowSkill_1();

	WidgetSwitcher_EF->SetActiveWidgetIndex(3);
}

// =============================================






// [칼]
// 칼의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
void USkillSettingWidget::OnHoveredSwordSkill_1()
{
	
	SkillLevelPoint = TextBlock_SL_Sword_1->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if(SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 5)*5;
	}
	else
	{
		Damage =  round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 5)*5;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt+1))))+ 5)*5;
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(0);
	
}

void USkillSettingWidget::OnHoveredSwordSkill_2()
{
	SkillLevelPoint = TextBlock_SL_Sword_2->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 150)*2;
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 150)*2;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 150)*2;
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(1);

	
}

void USkillSettingWidget::OnHoveredSwordSkill_3()
{
	SkillLevelPoint = TextBlock_SL_Sword_3->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 200);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 200);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 200);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(2);
}

// 칼의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
void USkillSettingWidget::OnClickSwordSkill_1_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Sword1 < 10)
		{
			CurrentSkillPoint--;
			Sword1++;
		}
	}
	
	//CurrentSkillPoint--;
	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));

	//Sword1++;
	TextBlock_SL_Sword_1->SetText(FText::AsNumber(Sword1));

	WidgetSwitcher_EF->SetActiveWidgetIndex(0);

	OnHoveredSwordSkill_1();

}

void USkillSettingWidget::OnClickSwordSkill_2_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Sword2 < 10)
		{
			CurrentSkillPoint--;
			Sword2++;
		}
	}
	
	//CurrentSkillPoint--;
	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));

	//Sword2++;
	TextBlock_SL_Sword_2->SetText(FText::AsNumber(Sword2));

	OnHoveredSwordSkill_2();

	WidgetSwitcher_EF->SetActiveWidgetIndex(1);
}

void USkillSettingWidget::OnClickSwordSkill_3_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Sword3 < 10)
		{
			CurrentSkillPoint--;
			Sword3++;
		}
	}
	//CurrentSkillPoint--;
	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));

	//Sword3++;
	TextBlock_SL_Sword_3->SetText(FText::AsNumber(Sword3));

	OnHoveredSwordSkill_3();

	WidgetSwitcher_EF->SetActiveWidgetIndex(2);
}

// =============================================




// [지팡이]
// 지팡이의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
void USkillSettingWidget::OnHoveredWandSkill_1()
{
	SkillLevelPoint = TextBlock_SL_Wand_1->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 100);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 100);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 100);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(3);
}

void USkillSettingWidget::OnHoveredWandSkill_2()
{
	SkillLevelPoint = TextBlock_SL_Wand_2->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 150);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 150);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 150);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(4);
}

void USkillSettingWidget::OnHoveredWandSkill_3()
{
	SkillLevelPoint = TextBlock_SL_Wand_3->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 300);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 300);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 300);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(5);
}
// 지팡이의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
void USkillSettingWidget::OnClickWandSkill_1_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Wand1 < 10)
		{
			CurrentSkillPoint--;
			Wand1++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Wand_1->SetText(FText::AsNumber(Wand1));

	OnHoveredWandSkill_1();

	WidgetSwitcher_EF->SetActiveWidgetIndex(0);
}

void USkillSettingWidget::OnClickWandSkill_2_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Wand2 < 10)
		{
			CurrentSkillPoint--;
			Wand2++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Wand_2->SetText(FText::AsNumber(Wand2));

	OnHoveredWandSkill_2();

	WidgetSwitcher_EF->SetActiveWidgetIndex(1);
}

void USkillSettingWidget::OnClickWandSkill_3_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Wand3 < 10)
		{
			CurrentSkillPoint--;
			Wand3++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Wand_3->SetText(FText::AsNumber(Wand3));

	OnHoveredWandSkill_3();

	WidgetSwitcher_EF->SetActiveWidgetIndex(2);
}

// =============================================





// [활]
// 활의 1, 2, 3번 스킬 (마우스를 위로 올리면 그 스킬에 대한 설명이 나온다)
void USkillSettingWidget::OnHoveredBowSkill_1()
{
	SkillLevelPoint = TextBlock_SL_Bow_1->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 5)*4;
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 5)*4;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 5)*4;
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(6);
}

void USkillSettingWidget::OnHoveredBowSkill_2()
{
	SkillLevelPoint = TextBlock_SL_Bow_2->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 400);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 400);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 400);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(7);
}

void USkillSettingWidget::OnHoveredBowSkill_3()
{
	SkillLevelPoint = TextBlock_SL_Bow_3->GetText();
	Text_Level->SetText(SkillLevelPoint);

	SkillLevelPointString = SkillLevelPoint.ToString();
	SkillLevelPointInt = FCString::Atoi(*SkillLevelPointString);

	if (SkillLevelPointInt == 0)
	{
		Damage = 0;
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 300);
	}
	else
	{
		Damage = round((SwordWeaponDmg * (1 + (0.1 * SkillLevelPointInt))) + 300);
		NextDamage = round((SwordWeaponDmg * (1 + (0.1 * (SkillLevelPointInt + 1)))) + 300);
	}

	DamageStirng = FString::SanitizeFloat(Damage);
	DamageText = FText::FromString(DamageStirng);

	NextDamageString = FString::SanitizeFloat(NextDamage);
	NextDamageText = FText::FromString(NextDamageString);

	Text_CurrentDmg->SetText(DamageText);
	Text_NextDmg->SetText(NextDamageText);

	SkillNameSwitcher->SetActiveWidgetIndex(8);
}
// 활의 1, 2, 3번 스킬을 업그레이드 할 수있는 버튼
void USkillSettingWidget::OnClickBowSkill_1_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Bow1 < 10)
		{
			CurrentSkillPoint--;
			Bow1++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Bow_1->SetText(FText::AsNumber(Bow1));


	OnHoveredBowSkill_1();

	WidgetSwitcher_EF->SetActiveWidgetIndex(0);
}

void USkillSettingWidget::OnClickBowSkill_2_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Bow2 < 10)
		{
			CurrentSkillPoint--;
			Bow2++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Bow_2->SetText(FText::AsNumber(Bow2));

	OnHoveredBowSkill_2();

	WidgetSwitcher_EF->SetActiveWidgetIndex(1);
}

void USkillSettingWidget::OnClickBowSkill_3_Upgrade()
{
	if (CurrentSkillPoint > 0)
	{
		if (Bow3 < 10)
		{
			CurrentSkillPoint--;
			Bow3++;
		}
	}

	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
	TextBlock_SL_Bow_3->SetText(FText::AsNumber(Bow3));

	OnHoveredBowSkill_3();

	WidgetSwitcher_EF->SetActiveWidgetIndex(2);
}

void USkillSettingWidget::SetSkillLevel()
{
	TextBlock_SL_Sword_1->SetText(FText::AsNumber(Sword1));
	TextBlock_SL_Sword_2->SetText(FText::AsNumber(Sword2));
	TextBlock_SL_Sword_3->SetText(FText::AsNumber(Sword3));
	TextBlock_SL_Wand_1->SetText(FText::AsNumber(Wand1));
	TextBlock_SL_Wand_2->SetText(FText::AsNumber(Wand2));
	TextBlock_SL_Wand_3->SetText(FText::AsNumber(Wand3));
	TextBlock_SL_Bow_1->SetText(FText::AsNumber(Bow1));
	TextBlock_SL_Bow_2->SetText(FText::AsNumber(Bow2));
	TextBlock_SL_Bow_3->SetText(FText::AsNumber(Bow3));
	TextBlock_SkillPoint->SetText(FText::AsNumber(CurrentSkillPoint));
}

// =============================================


