
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
	// ������ �� �ε����� ���
	// 0�� : Į ������ Ȱ��ȭ
	// 1�� : ������ ������ Ȱ��ȭ
	// 2�� : Ȱ ������ Ȱ��ȭ
	// 3�� : ��� ���� ��Ȱ��ȭ

	// �ʱ⿡�� ���⸦ �ƿ� �������� ���� ���·� ����
	WidgetSwitcher_MainPlayer->SetActiveWidgetIndex(0);
	// ��ų ������ ����ġ
	WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(0);

	// �ɼ� ��ư
	Button_Option->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickOptionButton);
	// ��ų ��ư
	Button_SKill->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickSkillButton);

	// ä�� ���� / �ݱ� ��ư
	Button_Chat->OnClicked.AddDynamic(this, &UMainPlayerWidget::OnClickChat);


	// �ʱ� ��� ����
	CurrentCoin = player->playerGold;
	TextBlock_Coin->SetText(FText::AsNumber(CurrentCoin));

	// �÷��̾� ����
	PlayerLevel = player->playerLevel;
	TextBlock_PlayerLevel->SetText(FText::AsNumber(PlayerLevel));

	// ������ �̸��� �ð��� �Ⱥ��̰� ����
	TextBlock_BlockTime->SetText(FText::FromString(""));

	// �ʱ� ����ġ 0���� ����
	ProgressBar_EXPBar->SetPercent(0);

	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	WidgetSwitcher_BuffDeBuff->SetVisibility(ESlateVisibility::Hidden);

	// ä��â ��� �� ������
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

// ���� ���� �� �߻��ϴ� �ִϸ��̼�
void UMainPlayerWidget::ChangeAnim()
{
	UUserWidget::PlayAnimation(ChangeWeaponAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}





// ���� Ŀ���͸���¡ �Ϸ� ����
void UMainPlayerWidget::ShowSystemM()
{
	if (bShowSystemM)
	{
		System_CreateMon->SetVisibility(ESlateVisibility::Visible);
		UUserWidget::PlayAnimation(OpenChat, 0, 1, EUMGSequencePlayMode::Forward, 1);
	}
}




// [Į]
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
////[������]
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

// ��ų ��Ÿ�� ������====================================
void UMainPlayerWidget::CoolTime_Skill(int32 index, float CoolTime)
{
	switch (index)
	{
	// Į
	case 0:
		ProgressBar_Skill_Sword_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword1"), "")->CoolTime);
		break;
	case 1:
		ProgressBar_Skill_Sword_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword2"), "")->CoolTime);
		break;
	case 2:
		ProgressBar_Skill_Sword_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword3"), "")->CoolTime);
		break;
	// ������
	case 3:
		ProgressBar_Skill_Wand_3->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic1"), "")->CoolTime);
		break;
	case 4:
		ProgressBar_Skill_Wand_2->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic2"), "")->CoolTime);
		break;
	case 5:
		ProgressBar_Skill_Wand_1->SetPercent(CoolTime / OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic3"), "")->CoolTime);
		break;
	// Ȱ
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


//[Ȱ]
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



// ä���� ���� ���� �� �ִ� ��ư
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


// �÷��̾� ������
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


// �÷��̾��� ü�� ������
void UMainPlayerWidget::HP_Update(float HP)
{
	Player_HPBar->SetPercent(HP/ 1000);
}


// �÷��̾��� ���� ������
void UMainPlayerWidget::MP_Update(float MP)
{
	Player_MPBar->SetPercent(MP/1000);
	//UE_LOG(LogTemp, Warning, TEXT("BJK MP : %f"), MP);
}

// �÷��̾� ����ġ ������
void UMainPlayerWidget::EXP_Update(AChallengersCharacter* target)
{
	ProgressBar_EXPBar->SetPercent((float) target->playerCurrentExp / (float) target->playerMaxExp);
	UE_LOG(LogTemp, Warning, TEXT("target->playerCurrentExp : %d"), target->playerCurrentExp);
	//ProgressBar_EXPBar->SetPercent(1);
}



// ���� ���̾ư��� �ִϸ��̼�======================================
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
		// ��ų ������ ����ġ
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
		// ��ų ������ ����ġ
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
		// ��ų ������ ����ġ
		WidgetSwitcher_SkillIcon->SetActiveWidgetIndex(2);
	}
}
//===============================================



// �ɼ� ��ư
void UMainPlayerWidget::OnClickOptionButton()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->CreateOptionWidget();
	
}

// ��ų ��ư
void UMainPlayerWidget::OnClickSkillButton()
{
	/*AMainPlayerController* PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->CreateSkillSetWidget();*/
}


// �� ���⸶�� �� ��� �׵θ� ��
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
	// �����ͺ� �ؽ�Ʈ�� ������� �ʴٸ�
	if (!Editable_chat->GetText().IsEmpty())
	{
		FString name = FString::Printf(TEXT("[%s]"), *player->playerName);
		// msg�� �����ͺ� �ؽ�Ʈ�� �����ִ� �ؽ�Ʈ�̴�
		FString msg = name + " " + Editable_chat->GetText().ToString();
		if (msg.IsEmpty())
		{
			return;
		}
		
		if (player)
		{
			player->ServerRPC_SendMsg(msg);
		}
		// ä��â�� �޽����� ���ϰ�, �����ͺ� �ؽ��z ��ĭ���� �����
		Editable_chat->SetText(FText::FromString(TEXT("")));
	}

}

void UMainPlayerWidget::AddMsg(const FString& msg)
{
	auto chat = CreateWidget<UChatWidget>(this, chatUI_BP);
	FText DisplayText = FText::FromString(msg); // FText ��ȯ
	chat->Text_msg->SetText(DisplayText); 	
	vertical_chat->AddChild(chat);
	ScrollBox_chat->ScrollToEnd();	
}

void UMainPlayerWidget::ActiveEditableChat()
{
	// ���͸� ���� ��, �����ͺ� �ؽ�Ʈ�� Ȱ��ȭ�ϰ�, Ű���� �Է��� ��Ŀ���� �������� �����Ѵ�
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

	// �����ͺ� �ؽ�Ʈ�� �޽��� �Է��� ������ ���͸� ���� ��
	if (CommitMethod == ETextCommit::OnEnter)
	{
		// �����ͺ� �ؽ�Ʈ�� ������� �ʴٸ� �޽����� ������
		if (Editable_chat->GetText().IsEmpty() == false)
		{
			OnMySendMsg();
			// �޽����� ������ Ű���� ��Ŀ���� �������� �����Ѵ�
			Editable_chat->SetKeyboardFocus();

			UE_LOG(LogTemp, Warning, TEXT("Viewport Message Sent"));
						

			return;
		}
		// �����ͺ� �ؽ�Ʈ�� ����ִٸ�
		if (Editable_chat->GetText().IsEmpty() == true)
		{
			// Ű���� ��Ŀ���� �÷��̾�� �ʱ�ȭ�Ѵ�
			FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::Cleared);

			Border_Chat->SetVisibility(ESlateVisibility::Visible);

			FLinearColor chatColor(0.005131f, 0.005208f, 0.004747f, 0.505f);
			chatColor = FLinearColor::MakeFromHSV8(70.021675 / 360 * 255, 0.088518 * 255, 0.005208 * 255);

			chatColor.A = 0.2f;
			Border_Chat->SetBrushColor(chatColor);

			// ���Ӹ�带 �����ϰ�
			pc->SetInputMode(FInputModeGameOnly());
			pc->SetShowMouseCursor(false);

			// ���콺 ĸ�ĸ�带 noCapture�� �����ؼ� ���콺�� ��Ȱ��ȭ ��Ų��
			UGameplayStatics::SetViewportMouseCaptureMode(GetWorld(), EMouseCaptureMode::NoCapture);
			pc->ResetIgnoreLookInput();

			UE_LOG(LogTemp, Warning, TEXT("Viewport DeactiveEditableChat End"));
		}
	}


	
}
