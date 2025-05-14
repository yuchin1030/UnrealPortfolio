#include "MainPlayerController.h"
#include "SelectCustomWidget.h"
#include "BJK/BattleNPCWidget.h"
#include "BJK/SkillSettingWidget.h"
#include "BJK/MainPlayerWidget.h"
#include "BJK/UpgradeWeaponNPCWidget.h"
#include "BJK/DungeonClearWidget.h"
#include "BJK/DungeonClearFailWidget.h"
#include "BJK/SelectCCWidget.h"
#include "BJK/LoadWidget.h"
#include "BJK/JoinBattle_ReadyWidget.h"
#include "Components/TextBlock.h"
#include "CHR/CreateRoomWidget.h"
#include "Yohan/EnemyCountInDungeonWidget.h"
#include "GJY/OptionUI.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "BJK/TutorialWidget.h"

// Ŀ���� NPC UI â ����
void AMainPlayerController::CreateSelectCustomWidget()
{
	if (selectCustomWidget_bp != nullptr)
	{
		selectCustomWidget = CreateWidget<USelectCustomWidget>(GetWorld(), selectCustomWidget_bp);
		if (selectCustomWidget)
		{
			selectCustomWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			SetShowMouseCursor(true);
		}
	}
}

// ��Ʋ NPC UI â ����
void AMainPlayerController::CreateBattleWidget()
{
	if (battleWidget_bp != nullptr)
	{
		battleWidget = CreateWidget<UCreateRoomWidget>(GetWorld(), battleWidget_bp);
		UE_LOG(LogTemp, Warning, TEXT("Widget OUT"));
		if (battleWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget IN"));
			battleWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			SetShowMouseCursor(true);
		}
	}
}


// ��ų��ȭ UI����
void AMainPlayerController::CreateSkillSetWidget()
{
	if (skillsetWidget_bp != nullptr)
	{
		skillsetWidget = CreateWidget<USkillSettingWidget>(GetWorld(), skillsetWidget_bp);
		if (skillsetWidget)
		{
			SetInputMode(FInputModeUIOnly());
			skillsetWidget->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}
// ���� �÷��̾� UI ����
void AMainPlayerController::CreateMainPlayerWidget()
{
	if (mainplayerWidget_bp != nullptr)
	{
		mainplayerWidget = CreateWidget<UMainPlayerWidget>(GetWorld(), mainplayerWidget_bp);
		if (mainplayerWidget)
		{
			mainplayerWidget->AddToViewport();
		}
	}
}

// ���� ��ȭ UI ����
void AMainPlayerController::CreateUpgradeWeaponWidget()
{
	if (upgradeWeaponWidget_bp != nullptr)
	{
		upgradeWeaponWidget = CreateWidget<UUpgradeWeaponNPCWidget>(GetWorld(), upgradeWeaponWidget_bp);
		if (upgradeWeaponWidget)
		{
			SetInputMode(FInputModeUIOnly());
			upgradeWeaponWidget->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}

// ���� Ŭ���� 
void AMainPlayerController::CreateDungeonClearWidget()
{
	if (dungeonClearWidget_bp != nullptr)
	{
		dungeonClearWidget = CreateWidget<UDungeonClearWidget>(GetWorld(), dungeonClearWidget_bp);
		if (dungeonClearWidget)
		{
			SetInputMode(FInputModeUIOnly());
			dungeonClearWidget->AddToViewport();
			SetShowMouseCursor(true);
			UGameplayStatics::PlaySound2D(GetWorld(), clearSound);
		}
	}
}
// ���� Ŭ���� ����
void AMainPlayerController::CreateDungeonClearFailWidget()
{
	if (dungeonClearFailWidget_bp != nullptr)
	{
		dungeonClearFailWidget = CreateWidget<UDungeonClearFailWidget>(GetWorld(), dungeonClearFailWidget_bp);
		if (dungeonClearFailWidget)
		{
			SetInputMode(FInputModeUIOnly());
			dungeonClearFailWidget->AddToViewport();
			SetShowMouseCursor(true);
			UGameplayStatics::PlaySound2D(GetWorld(), failSound);
		}
	}
}

// �ε�or����
void AMainPlayerController::CreateLoadWidget()
{
	if (loadWidget_bp != nullptr)
	{
		loadWidget = CreateWidget<ULoadWidget>(GetWorld(), loadWidget_bp);
		if (loadWidget)
		{
			loadWidget->AddToViewport();
		}
	}
}
// ������ ���� �� �����غ� UI����
void AMainPlayerController::CreateBattleReadyWidget()
{
	if (battleReadyWidget_bp != nullptr)
	{
		battleReadyWidget = CreateWidget<UJoinBattle_ReadyWidget>(GetWorld(), battleReadyWidget_bp);
		if (battleReadyWidget)
		{
			battleReadyWidget->AddToViewport();
		}
	}
}

// �ɼ� UI ����
void AMainPlayerController::CreateOptionWidget()
{
	if (OptionUI_bp != nullptr)
	{
		OptionWidget = CreateWidget<UOptionUI>(GetWorld(), OptionUI_bp);
		if (OptionWidget)
		{
			OptionWidget->AddToViewport();
			
		}
	}

}
// Ʃ�丮�� UI ����
void AMainPlayerController::CreateTutorialWidget()
{
	if (tutorialWidget_bp != nullptr)
	{
		tutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), tutorialWidget_bp);
		if (tutorialWidget)
		{
			SetInputMode(FInputModeUIOnly());
			tutorialWidget->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}

void AMainPlayerController::ShowBuff(int32 RandomIndex)
{
	if (mainplayerWidget)
	{
		mainplayerWidget->ShowBuff(RandomIndex);
	}
}






