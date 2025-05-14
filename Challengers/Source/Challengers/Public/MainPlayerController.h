#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class CHALLENGERS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	
	// ����, ����, ���� Ŀ���͸���¡ NPC�� UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USelectCustomWidget> selectCustomWidget_bp;
	
	// ������ ���� NPC UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UCreateRoomWidget> battleWidget_bp;

	// ��ų��ȭ UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USkillSettingWidget> skillsetWidget_bp;

	// ���� �÷��̾� UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UMainPlayerWidget> mainplayerWidget_bp;

	// ���Ⱝȭ NPC UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UUpgradeWeaponNPCWidget> upgradeWeaponWidget_bp;

	// ���� Ŭ���� �� UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UDungeonClearWidget> dungeonClearWidget_bp;

	// ���� Ŭ���� ���� �� UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UDungeonClearFailWidget> dungeonClearFailWidget_bp;

	// ĳ���� Ŀ���͸���¡ �������� UI����
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USelectCCWidget> selectCCWidget_bp;

	// �ε� or ���� UI����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class ULoadWidget> loadWidget_bp;

	// ������ ���� �� �����غ� UI����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UJoinBattle_ReadyWidget> battleReadyWidget_bp;

	// �ɼ� UI ����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UOptionUI> OptionUI_bp;

	// Ʃ�丮�� UI ����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UTutorialWidget> tutorialWidget_bp;

	// ���� Ŭ���� ����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	class USoundBase* clearSound;

	// ���� Ŭ���� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	class USoundBase* failSound;

public:
	
	// Ŀ���͸���¡ Widget���� ����
	UPROPERTY()
	class USelectCustomWidget* selectCustomWidget;

	// ��Ʋ Widget���� ����
	UPROPERTY()
	class UCreateRoomWidget* battleWidget;

	// ��ų��ȭ Widget���� ����
	UPROPERTY()
	class USkillSettingWidget* skillsetWidget;

	// ���� Widget���� ����
	UPROPERTY(BlueprintReadWrite)
	class UMainPlayerWidget* mainplayerWidget;

	// ���Ⱝȭ NPC UI����
	UPROPERTY()
	class UUpgradeWeaponNPCWidget* upgradeWeaponWidget;

	// ���� Ŭ���� �� UI����
	UPROPERTY()
	class UDungeonClearWidget* dungeonClearWidget;

	// ���� Ŭ���� ���� �� UI����
	UPROPERTY()
	class UDungeonClearFailWidget* dungeonClearFailWidget;

	// ĳ���� Ŀ���͸���¡ �������� UI����
	UPROPERTY()
	class USelectCCWidget* selectCCWidget;

	// �ε� or ���� UI����
	UPROPERTY()
	class ULoadWidget* loadWidget;

	// ������ ���� �� �����غ� UI����
	UPROPERTY()
	class UJoinBattle_ReadyWidget* battleReadyWidget;

	//�ɼ� UI ���� ����
	UPROPERTY()
	class UOptionUI* OptionWidget;

	// Ʃ�丮�� UI ����
	UPROPERTY()
	class UTutorialWidget* tutorialWidget;


	// ����, ����, ���� Ŀ���͸���¡ NPC�� UI���� ���
	void CreateSelectCustomWidget();

	// ������ ���� UI����
	void CreateBattleWidget();

	// ��ų��ȭ UI����
	void CreateSkillSetWidget();

	// ���� �÷��̾� UI����
	void CreateMainPlayerWidget();

	// ���Ⱝȭ NPC UI����
	void CreateUpgradeWeaponWidget();

	// ���� Ŭ���� �� UI����
	void CreateDungeonClearWidget();

	// ���� Ŭ���� ���� �� UI����
	void CreateDungeonClearFailWidget();

	// �ε� or ���� UI����
	void CreateLoadWidget();

	// ������ ���� �� �����غ� UI����
	void CreateBattleReadyWidget();

	// �ɼ� UI ����
	void CreateOptionWidget();

	// Ʃ�丮�� UI ����
	void CreateTutorialWidget();

	
	void ShowBuff(int32 RandomIndex);
};
