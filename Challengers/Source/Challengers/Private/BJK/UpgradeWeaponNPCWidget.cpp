#include "BJK/UpgradeWeaponNPCWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "BJK/MainPlayerWidget.h"
#include "MainPlayerController.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>


void UUpgradeWeaponNPCWidget::NativeConstruct()
{

	Super::NativeConstruct();

	// ������
	WidgetSwitcher_SelectUpgrade_Weapon->SetActiveWidgetIndex(0);

	// â �ݱ�
	Button_Close->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickClose);

	player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AMainPlayerController* pc = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// �ʱ⿡ ���� ���ⷹ�� 1���� ����
	TextBlock_Level_Sword->SetText(FText::AsNumber(player->weaponLevel[0]));
	TextBlock_Level_Wand->SetText(FText::AsNumber(player->weaponLevel[1]));
	TextBlock_Level_Bow->SetText(FText::AsNumber(player->weaponLevel[2]));


	// ���� ���� ���ݷ� �ʱ� ��
	TextBlock_CunrrentStat_Sword->SetText(FText::AsNumber(player->currentWeaponStat[0]));
	TextBlock_CunrrentStat_Wand->SetText(FText::AsNumber(player->currentWeaponStat[1]));
	TextBlock_CunrrentStat_Bow->SetText(FText::AsNumber(player->currentWeaponStat[2]));


	// ��ȭ ���� ���ݷ� �ʱ� ��
	TextBlock_NextStat_Sword->SetText(FText::AsNumber(player->nextWeaponStat[0]));
	TextBlock_NextStat_Wand->SetText(FText::AsNumber(player->nextWeaponStat[1]));
	TextBlock_NextStat_Bow->SetText(FText::AsNumber(player->nextWeaponStat[2]));


	// ��ȭ�� �Ҹ�Ǵ� ��差 �ʱ� �� 
	TextBlock_NeedMoney_Sword->SetText(FText::AsNumber(player->upgWeaponNeedGold[0]));
	TextBlock_NeedMoney_Wand->SetText(FText::AsNumber(player->upgWeaponNeedGold[1]));
	TextBlock_NeedMoney_Bow->SetText(FText::AsNumber(player->upgWeaponNeedGold[2]));



	// "��ȭ �Ͻðڽ��ϱ�" ���� ���� ��ư �� �ݱ�
	Button_OpenSystem_sword->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickOpenSystem_sword);
	Button_Sword_Close->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickButton_Sword_Close);
	Button_OpenSystem_wand->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickOpenSystem_wand);
	Button_Wand_Close->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickButton_Wand_Close);
	Button_OpenSystem_bow->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickOpenSystem_bow);
	Button_Bow_Close->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickButton_Bow_Close);
	



	// ����⸦ ���� �� �������� ���� ��ư
	Button_SelectWeapon_Sword->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Sword);
	Button_SelectWeapon_Wand->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Wand);
	Button_SelectWeapon_Bow->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Bow);


	// ����⸦ ��ȭ �� �������� ���� ��ư
	Button_Upgrade_Sword->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickUpgrade_Sword);
	Button_Upgrade_Wand->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickUpgrade_Wand);
	Button_Upgrade_Bow->OnClicked.AddDynamic(this, &UUpgradeWeaponNPCWidget::OnClickUpgrade_Bow);

	pc->mainplayerWidget->TextBlock_Coin->SetVisibility(ESlateVisibility::Visible);
	pc->mainplayerWidget->Image_Coin->SetVisibility(ESlateVisibility::Visible);


	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);

	UpgreadeWeaponNPCSound();
}

void UUpgradeWeaponNPCWidget::UpgreadeWeaponNPCSound()
{
	if (NPCSoundPlay)
	{
		UGameplayStatics::PlaySound2D(this, NPCSoundPlay);
	}
}

// â�ݱ�
void UUpgradeWeaponNPCWidget::OnClickClose()
{
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	AMainPlayerController* pc = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Hidden);
	bClosed = true;
	if (player != nullptr)
	{
		player->CanWalk();
	}

	pc->mainplayerWidget->TextBlock_Coin->SetVisibility(ESlateVisibility::Hidden);
	pc->mainplayerWidget->Image_Coin->SetVisibility(ESlateVisibility::Hidden);

	player->bShowWeaponUpgradeNPC = false;
}



// ��ȭ �� ���� ���� ===================================
// Į
void UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Sword()
{
	WidgetSwitcher_SelectUpgrade_Weapon->SetActiveWidgetIndex(0);
	
	currentSwitcherIndex = 0;
}
// ������
void UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Wand()
{
	WidgetSwitcher_SelectUpgrade_Weapon->SetActiveWidgetIndex(1);

	currentSwitcherIndex = 1;
}
// Ȱ
void UUpgradeWeaponNPCWidget::OnClickSelectWeapon_Bow()
{
	WidgetSwitcher_SelectUpgrade_Weapon->SetActiveWidgetIndex(2);

	currentSwitcherIndex = 2;
}
// =============================================





void UUpgradeWeaponNPCWidget::OnClickOpenSystem_sword()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_bUpgrade->SetActiveWidgetIndex(0);
}

// ��ȭ�ϱ� ��ư ������ =============================
// Į
void UUpgradeWeaponNPCWidget::OnClickUpgrade_Sword()
{	
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
	
	player->UpgradeWeapon();

	// ���������� �ؽ�Ʈ�� ǥ�õǴ� ��
	TextBlock_Level_Sword->SetText(FText::AsNumber(player->weaponLevel[0]));
	TextBlock_CunrrentStat_Sword->SetText(FText::AsNumber(player->currentWeaponStat[0]));
	TextBlock_NextStat_Sword->SetText(FText::AsNumber(player->nextWeaponStat[0]));
	TextBlock_NeedMoney_Sword->SetText(FText::AsNumber(player->upgWeaponNeedGold[0]));
	player->pc->mainplayerWidget->SpendCoin();

	UE_LOG(LogTemp, Warning, TEXT("Load :: playerName : %s, playerGold : %d, weaponLevel : %d, currentWeaponStat : %d, upgWeaponNeedGold : %d"), *player->playerName, player->playerGold, player->weaponLevel[0], player->currentWeaponStat[0], player->upgWeaponNeedGold[0]);

	if (player->weaponLevel[0] == 20)
	{
		TextBlock_NextStat_Sword->SetText(FText::FromString("-"));
		TextBlock_NeedMoney_Sword->SetText(FText::FromString("-"));
	}

}

void UUpgradeWeaponNPCWidget::OnClickButton_Sword_Close()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
}





// ������
void UUpgradeWeaponNPCWidget::OnClickOpenSystem_wand()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_bUpgrade->SetActiveWidgetIndex(1);
}

void UUpgradeWeaponNPCWidget::OnClickUpgrade_Wand()
{
	player->UpgradeWeapon();

	// ���������� �ؽ�Ʈ�� ǥ�õǴ� ��
	TextBlock_Level_Wand->SetText(FText::AsNumber(player->weaponLevel[1]));
	TextBlock_CunrrentStat_Wand->SetText(FText::AsNumber(player->currentWeaponStat[1]));
	TextBlock_NextStat_Wand->SetText(FText::AsNumber(player->nextWeaponStat[1]));
	TextBlock_NeedMoney_Wand->SetText(FText::AsNumber(player->upgWeaponNeedGold[1]));
	player->pc->mainplayerWidget->SpendCoin();

	if (player->weaponLevel[1] == 20)
	{
		TextBlock_NextStat_Wand->SetText(FText::FromString("-"));
		TextBlock_NeedMoney_Wand->SetText(FText::FromString("-"));
	}
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
}

void UUpgradeWeaponNPCWidget::OnClickButton_Wand_Close()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
}




// Ȱ
void UUpgradeWeaponNPCWidget::OnClickOpenSystem_bow()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_bUpgrade->SetActiveWidgetIndex(2);
}

void UUpgradeWeaponNPCWidget::OnClickUpgrade_Bow()
{
	player->UpgradeWeapon();

	// ���������� �ؽ�Ʈ�� ǥ�õǴ� ��
	TextBlock_Level_Bow->SetText(FText::AsNumber(player->weaponLevel[2]));
	TextBlock_CunrrentStat_Bow->SetText(FText::AsNumber(player->currentWeaponStat[2]));
	TextBlock_NextStat_Bow->SetText(FText::AsNumber(player->nextWeaponStat[2]));
	TextBlock_NeedMoney_Bow->SetText(FText::AsNumber(player->upgWeaponNeedGold[2]));
	player->pc->mainplayerWidget->SpendCoin();

	if (player->weaponLevel[2] == 20)
	{
		TextBlock_NextStat_Bow->SetText(FText::FromString("-"));
		TextBlock_NeedMoney_Bow->SetText(FText::FromString("-"));
	}
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
}
void UUpgradeWeaponNPCWidget::OnClickButton_Bow_Close()
{
	WidgetSwitcher_bUpgrade->SetVisibility(ESlateVisibility::Hidden);
}
// =============================================
