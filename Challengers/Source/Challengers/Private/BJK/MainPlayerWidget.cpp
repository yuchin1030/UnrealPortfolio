
#include "BJK/MainPlayerWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MainPlayerController.h"
#include "Components/ProgressBar.h"
#include "ChallengersCharacter.h"
#include "BJK/BuffDebuffManager.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include "OurGameInstance.h"
#include "SkillStruct.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableText.h>
#include "Yohan/ChatWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>
#include <../../../../../../../Source/Runtime/Core/Public/Delegates/Delegate.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Border.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/MultiLineEditableText.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/MultiLineEditableTextBox.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/VerticalBox.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/RichTextBlock.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>

void UMainPlayerWidget::NativeConstruct()
{
	player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// 스위쳐 각 인덱스의 기능
	// 0번 : 칼 장착시 활성화
	// 1번 : 지팡이 장착시 활성화
	// 2번 : 활 장착시 활성화
	// 3번 : 모든 무기 비활성화

	// 초기에는 무기를 아예 장착하지 않은 상태로 시작
	WidgetSwitcher_MainPlayer->SetActiveWidgetIndex(0);
	// 스킬 아이콘 스위치
	WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(0);

	// 옵션 버튼
	Button_Option->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickOptionButton);
	// 스킬 버튼
	Button_SKill->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickSkillButton);

	// 채팅 열기 / 닫기 버튼
	Button_Chat->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickChat);


	// 초기 골드 설정
	CurrentCoin = player->playerGold;
	TextBlock_Coin->SetText(FText::AsNumber(CurrentCoin));

	// 플레이어 레벨
	PlayerLevel = player->playerLevel;
	TextBlock_PlayerLevel->SetText(FText::AsNumber(PlayerLevel));

	// 버프의 이름과 시간초 안보이게 설정
	TextBlock_BlockTime->SetText(FText::FromString(""));

	// 초기 경험치 0으로 설정
	ProgressBar_EXPBar->SetPercent(0);

	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	WidgetSwitcher_BuffDeBuff->SetVisibility(ESlateVisibility::Hidden);

	// 채팅창 배경 색 설정정
	Editable_chat->OnTextCommitted.AddDynamic(this, &UMainPlayerWidget::DeActiveEditableChat);

	Border_Chat->SetVisibility(ESlateVisibility::Visible);

	FLinearColor chatColor(0.005131f, 0.005208f, 0.004747f, 0.505f);
	chatColor = FLinearColor::MakeFromHSV8(70.021675 / 360 * 255, 0.088518 * 255, 0.005208 * 255);

	chatColor.A = 0.2f;
	Border_Chat->SetBrushColor(chatColor);
}


void UMainPlayerWidget::ShowBuff(int32 BuffNum)
{
	WidgetSwitcher_BuffDeBuff->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_BuffDeBuff->SetActiveWidgetIndex(BuffNum);
	if (BuffNum==0 && BuffNum %2==0)
	{
		if (BuffSound)
		{
			UGameplayStatics::PlaySound2D(this, BuffSound);
		}

	}
	else
	{
		if (DeBuffSound)
		{
			UGameplayStatics::PlaySound2D(this, DeBuffSound);
		}
	}
}

void UMainPlayerWidget::HiddenBuff()
{
	WidgetSwitcher_BuffDeBuff->SetVisibility(ESlateVisibility::Hidden);
}

// 무기 변경 시 발생하는 애니메이션
void UMainPlayerWidget::ChangeAnim()
{
	UUserWidget::PlayAnimation(ChangeWeaponAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}





// 몬스터 커스터마이징 완료 문구
void UMainPlayerWidget::ShowSystemM()
{
	if (bShowSystemM)
	{
		System_CreateMon->SetVisibility(ESlateVisibility::Visible);
		UUserWidget::PlayAnimation(OpenChat, 0, 1, EUMGSequencePlayMode::Forward, 1);
	}
}




// [칼]
//void UMainPlayerWidget::CoolTime_Skill_Sword1(float CoolTime)
//{
//	ProgressBar_Skill_Sword_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword1"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Sword2(float CoolTime)
//{
//	ProgressBar_Skill_Sword_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword2"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Sword3(float CoolTime)
//{
//	ProgressBar_Skill_Sword_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword3"), "")->CoolTime);
//}
//
//
//
////[지팡이]
//void UMainPlayerWidget::CoolTime_Skill_Wand1(float CoolTime)
//{
//	ProgressBar_Skill_Wand_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic1"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Wand2(float CoolTime)
//{
//	ProgressBar_Skill_Wand_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic2"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Wand3(float CoolTime)
//{
//	ProgressBar_Skill_Wand_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic3"), "")->CoolTime);
//}

// 스킬 쿨타임 게이지====================================
void UMainPlayerWidget::CoolTime_Skill(int32 index, float CoolTime)
{
	switch (index)
	{
	// 칼
	case 0:
		ProgressBar_Skill_Sword_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword1"), "")->CoolTime);
		break;
	case 1:
		ProgressBar_Skill_Sword_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword2"), "")->CoolTime);
		break;
	case 2:
		ProgressBar_Skill_Sword_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword3"), "")->CoolTime);
		break;
	// 지팡이
	case 3:
		ProgressBar_Skill_Wand_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic1"), "")->CoolTime);
		break;
	case 4:
		ProgressBar_Skill_Wand_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic2"), "")->CoolTime);
		break;
	case 5:
		ProgressBar_Skill_Wand_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic3"), "")->CoolTime);
		break;
	// 활
	case 6:
		ProgressBar_Skill_Bow_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun1"), "")->CoolTime);
		break;
	case 7:
		ProgressBar_Skill_Bow_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun2"), "")->CoolTime);
		break;
	case 8:
		ProgressBar_Skill_Bow_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun3"), "")->CoolTime);
		break;
	default:
		break;
	}
}


//[활]
//void UMainPlayerWidget::CoolTime_Skill_Bow1(float CoolTime)
//{
//	ProgressBar_Skill_Bow_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun1"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Bow2(float CoolTime)
//{
//	ProgressBar_Skill_Bow_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun2"), "")->CoolTime);
//}
//
//void UMainPlayerWidget::CoolTime_Skill_Bow3(float CoolTime)
//{
//	ProgressBar_Skill_Bow_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun3"), "")->CoolTime);
//}

//===============================================



// 채팅을 열고 닫을 수 있는 버튼
void UMainPlayerWidget::OnClickChat()
{
	Num++;
	if (Num % 2 == 0)
	{
		UUserWidget::PlayAnimation(CloseChat, 0, 1, EUMGSequencePlayMode::Forward, 1);
		Image_Chat_Close->SetVisibility(ESlateVisibility::Hidden);
	
	}
	if (Num % 2 != 0)
	{
		UUserWidget::PlayAnimation(OpenChat, 0, 1, EUMGSequencePlayMode::Forward, 1);
		Image_Chat_Close->SetVisibility(ESlateVisibility::Visible);
	}
}


// 플레이어 소지금
void UMainPlayerWidget::SpendCoin()	// (int32 Amount)
{

	//if (CurrentCoin >= Amount)
	//{
	//	CurrentCoin -= Amount;

	//	if (TextBlock_Coin)
	//	{
	//		TextBlock_Coin->SetText(FText::AsNumber(CurrentCoin));
	//	}
	//	return true;
	//}

	//return false;

	TextBlock_Coin->SetText(FText::AsNumber(player->playerGold));
}


// 플레이어의 체력 게이지
void UMainPlayerWidget::HP_Update(float HP)
{
	Player_HPBar->SetPercent(HP/ 1000);
}


// 플레이어의 마나 게이지
void UMainPlayerWidget::MP_Update(float MP)
{
	Player_MPBar->SetPercent(MP/1000);
	//UE_LOG(LogTemp, Warning, TEXT("BJK MP : %f"), MP);
}

// 플레이어 경험치 게이지
void UMainPlayerWidget::EXP_Update(AChallengersCharacter* target)
{
	ProgressBar_EXPBar->SetPercent((float) target->playerCurrentExp / (float) target->playerMaxExp);
	UE_LOG(LogTemp, Warning, TEXT("target->playerCurrentExp : %d"), target->playerCurrentExp);
	//ProgressBar_EXPBar->SetPercent(1);
}



// 무기 나이아가라 애니메이션======================================
void UMainPlayerWidget::AnimSword(int32 WeaponNum)
{
	if (WeaponNum == 0)
	{
		UUserWidget::PlayAnimation(AnimSelectSword, 0,1, EUMGSequencePlayMode::Forward,1);
		UUserWidget::PlayAnimation(RotSword, 0,0, EUMGSequencePlayMode::Forward,0.5);
		UUserWidget::StopAnimation(AnimSelectWand);
		UUserWidget::StopAnimation(AnimSelectBow);
		UUserWidget::StopAnimation(RotWand);
		UUserWidget::StopAnimation(RotBow);
		// 스킬 아이콘 스위치
		WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(0);
	}

}

void UMainPlayerWidget::AnimWand(int32 WeaponNum)
{

	if (WeaponNum == 1)
	{
		UUserWidget::PlayAnimation(AnimSelectWand, 0, 1, EUMGSequencePlayMode::Forward, 1);
		UUserWidget::PlayAnimation(RotWand, 0, 0, EUMGSequencePlayMode::Forward, 0.5);
		UUserWidget::StopAnimation(AnimSelectSword);
		UUserWidget::StopAnimation(AnimSelectBow);
		UUserWidget::StopAnimation(RotSword);
		UUserWidget::StopAnimation(RotBow);
		// 스킬 아이콘 스위치
		WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(1);
	}
}

void UMainPlayerWidget::AnimBow(int32 WeaponNum)
{

	if (WeaponNum == 2)
	{
		UUserWidget::PlayAnimation(AnimSelectBow, 0, 1, EUMGSequencePlayMode::Forward, 1);
		UUserWidget::PlayAnimation(RotBow, 0, 0, EUMGSequencePlayMode::Forward, 0.5);
		UUserWidget::StopAnimation(AnimSelectWand);
		UUserWidget::StopAnimation(AnimSelectSword);
		UUserWidget::StopAnimation(RotWand);
		UUserWidget::StopAnimation(RotSword);
		// 스킬 아이콘 스위치
		WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(2);
	}
}
//===============================================



// 옵션 버튼
void UMainPlayerWidget::OnClickOptionButton()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->CreateOptionWidget();
	
}

// 스킬 버튼
void UMainPlayerWidget::OnClickSkillButton()
{
	/*AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->CreateSkillSetWidget();*/
}


// 각 무기마다 뒷 배경 테두리 색
void UMainPlayerWidget::ChangeSwitcher()
{
	WidgetSwitcher_MainPlayer->SetActiveWidgetIndex(weaponNum);
	if (weaponNum == 0)
	{
		Image_Red->SetVisibility(ESlateVisibility::Visible);
		Image_Yellow->SetVisibility(ESlateVisibility::Hidden);
		Image_Green->SetVisibility(ESlateVisibility::Hidden);
	}

	if (weaponNum == 1)
	{
		Image_Red->SetVisibility(ESlateVisibility::Hidden);
		Image_Yellow->SetVisibility(ESlateVisibility::Visible);
		Image_Green->SetVisibility(ESlateVisibility::Hidden);
	}

	if (weaponNum == 2)
	{
		Image_Red->SetVisibility(ESlateVisibility::Hidden);
		Image_Yellow->SetVisibility(ESlateVisibility::Hidden);
		Image_Green->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainPlayerWidget::OnMySendMsg()
{	
	// 에디터블 텍스트가 비어있지 않다면
	if (!Editable_chat->GetText().IsEmpty())
	{
		FString name = FString::Printf(TEXT("[%s]"), *player->playerName);
		// msg는 에디터블 텍스트에 적혀있는 텍스트이다
		FString msg = name + " " + Editable_chat->GetText().ToString();
		if (msg.IsEmpty())
		{
			return;
		}
		
		if (player)
		{
			player->ServerRPC_SendMsg(msg);
		}
		// 채팅창에 메시지를 더하고, 에디터블 텍스틑 빈칸으로 만든다
		Editable_chat->SetText(FText::FromString(TEXT("")));
	}

}

void UMainPlayerWidget::AddMsg(const FString& msg)
{
	auto chat = CreateWidget<UChatWidget>(this, chatUI_BP);
	FText DisplayText = FText::FromString(msg); // FText 변환
	chat->Text_msg->SetText(DisplayText); 	
	vertical_chat->AddChild(chat);
	ScrollBox_chat->ScrollToEnd();	
}

void UMainPlayerWidget::ActiveEditableChat()
{
	// 엔터를 쳤을 때, 에디터블 텍스트를 활성화하고, 키보드 입력의 포커스를 위젯으로 변경한다
	FSlateApplication::Get().SetKeyboardFocus(Editable_chat->TakeWidget());

	Border_Chat->SetVisibility(ESlateVisibility::Visible);
	
	FLinearColor chatColor(0.005131f, 0.005208f, 0.004747f, 0.505f);
	chatColor = FLinearColor::MakeFromHSV8(70.021675 / 360 * 255, 0.088518 * 255, 0.005208 * 255);
	
	chatColor.A = 0.5f;
	Border_Chat->SetBrushColor(chatColor);

	UE_LOG(LogTemp, Warning, TEXT("Viewport ActiveEditableChat End"));
}

void UMainPlayerWidget::DeActiveEditableChat(const FText& Text, ETextCommit::Type CommitMethod)
{
	auto pc = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 에디터블 텍스트에 메시지 입력이 끝나고 엔터를 쳤을 때
	if (CommitMethod == ETextCommit::OnEnter)
	{
		// 에디터블 텍스트가 비어있지 않다면 메시지를 보낸다
		if (Editable_chat->GetText().IsEmpty() == false)
		{
			OnMySendMsg();
			// 메시지를 보내고 키보드 포커스는 위젯으로 유지한다
			Editable_chat->SetKeyboardFocus();

			UE_LOG(LogTemp, Warning, TEXT("Viewport Message Sent"));
						

			return;
		}
		// 에디터블 텍스트가 비어있다면
		if (Editable_chat->GetText().IsEmpty() == true)
		{
			// 키보드 포커스를 플레이어로 초기화한다
			FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::Cleared);

			Border_Chat->SetVisibility(ESlateVisibility::Visible);

			FLinearColor chatColor(0.005131f, 0.005208f, 0.004747f, 0.505f);
			chatColor = FLinearColor::MakeFromHSV8(70.021675 / 360 * 255, 0.088518 * 255, 0.005208 * 255);

			chatColor.A = 0.2f;
			Border_Chat->SetBrushColor(chatColor);

			// 게임모드를 변경하고
			pc->SetInputMode(FInputModeGameOnly());
			pc->SetShowMouseCursor(false);

			// 마우스 캡쳐모드를 noCapture로 변경해서 마우스를 비활성화 시킨다
			UGameplayStatics::SetViewportMouseCaptureMode(GetWorld(), EMouseCaptureMode::NoCapture);
			pc->ResetIgnoreLookInput();

			UE_LOG(LogTemp, Warning, TEXT("Viewport DeactiveEditableChat End"));
		}
	}


	
}
