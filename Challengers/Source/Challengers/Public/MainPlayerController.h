#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class CHALLENGERS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	
	// 몬스터, 보스, 던전 커스터마이징 NPC의 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USelectCustomWidget> selectCustomWidget_bp;
	
	// 전투방 참가 NPC UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UCreateRoomWidget> battleWidget_bp;

	// 스킬강화 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USkillSettingWidget> skillsetWidget_bp;

	// 메인 플레이어 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UMainPlayerWidget> mainplayerWidget_bp;

	// 무기강화 NPC UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UUpgradeWeaponNPCWidget> upgradeWeaponWidget_bp;

	// 던전 클리어 시 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UDungeonClearWidget> dungeonClearWidget_bp;

	// 던전 클리어 실패 시 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class UDungeonClearFailWidget> dungeonClearFailWidget_bp;

	// 캐릭터 커스터마이징 최종문구 UI띄우기
	UPROPERTY(EditDefaultsOnly,Category = Widget)
	TSubclassOf<class USelectCCWidget> selectCCWidget_bp;

	// 로드 or 생성 UI띄우기
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class ULoadWidget> loadWidget_bp;

	// 전투방 입장 시 전투준비 UI띄우기
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UJoinBattle_ReadyWidget> battleReadyWidget_bp;

	// 옵션 UI 띄우기
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UOptionUI> OptionUI_bp;

	// 튜토리얼 UI 띄우기
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<class UTutorialWidget> tutorialWidget_bp;

	// 던전 클리어 사운드
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	class USoundBase* clearSound;

	// 던전 클리어 실패 사운드
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	class USoundBase* failSound;

public:
	
	// 커스터마이징 Widget변수 선언
	UPROPERTY()
	class USelectCustomWidget* selectCustomWidget;

	// 배틀 Widget변수 선언
	UPROPERTY()
	class UCreateRoomWidget* battleWidget;

	// 스킬강화 Widget변수 선언
	UPROPERTY()
	class USkillSettingWidget* skillsetWidget;

	// 메인 Widget변수 선언
	UPROPERTY(BlueprintReadWrite)
	class UMainPlayerWidget* mainplayerWidget;

	// 무기강화 NPC UI띄우기
	UPROPERTY()
	class UUpgradeWeaponNPCWidget* upgradeWeaponWidget;

	// 던전 클리어 시 UI띄우기
	UPROPERTY()
	class UDungeonClearWidget* dungeonClearWidget;

	// 던전 클리어 실패 시 UI띄우기
	UPROPERTY()
	class UDungeonClearFailWidget* dungeonClearFailWidget;

	// 캐릭터 커스터마이징 최종문구 UI띄우기
	UPROPERTY()
	class USelectCCWidget* selectCCWidget;

	// 로드 or 생성 UI띄우기
	UPROPERTY()
	class ULoadWidget* loadWidget;

	// 전투방 입장 시 전투준비 UI띄우기
	UPROPERTY()
	class UJoinBattle_ReadyWidget* battleReadyWidget;

	//옵션 UI 변수 선언
	UPROPERTY()
	class UOptionUI* OptionWidget;

	// 튜토리얼 UI 띄우기
	UPROPERTY()
	class UTutorialWidget* tutorialWidget;


	// 몬스터, 보스, 던전 커스터마이징 NPC의 UI띄우는 기능
	void CreateSelectCustomWidget();

	// 전투방 참가 UI띄우기
	void CreateBattleWidget();

	// 스킬강화 UI띄우기
	void CreateSkillSetWidget();

	// 메인 플레이어 UI띄우기
	void CreateMainPlayerWidget();

	// 무기강화 NPC UI띄우기
	void CreateUpgradeWeaponWidget();

	// 던전 클리어 시 UI띄우기
	void CreateDungeonClearWidget();

	// 던전 클리어 실패 시 UI띄우기
	void CreateDungeonClearFailWidget();

	// 로드 or 생성 UI띄우기
	void CreateLoadWidget();

	// 전투방 입장 시 전투준비 UI띄우기
	void CreateBattleReadyWidget();

	// 옵션 UI 띄우기
	void CreateOptionWidget();

	// 튜토리얼 UI 띄우기
	void CreateTutorialWidget();

	
	void ShowBuff(int32 RandomIndex);
};
