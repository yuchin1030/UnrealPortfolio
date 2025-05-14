// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BJK/BuffDebuffManager.h"
#include "OurGameModeBase.generated.h"

DECLARE_DELEGATE(FLoadingEnd);

/**
 * 
 */
UCLASS()
class CHALLENGERS_API AOurGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOurGameModeBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	FLoadingEnd loadingEndDelegate;

	// 현재 위치한 에너미의 총 갯수, 0이되면 게임이 끝나므로 1로 초기화
	UPROPERTY(replicated)
	int32 enemyTotal = 1;

	UPROPERTY(replicated)
	int32 enemyCurrent;

	UPROPERTY()
	class AMainPlayerController* pc;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseEnemy> enemy_BP;

	UPROPERTY()
	bool bDungeonFinished = false;

	UPROPERTY(Replicated)
	bool bDungoenLoadStart;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UDungeonClearFailWidget> dunClearFailUI_BP;

	UPROPERTY()
	class UDungeonClearFailWidget* dunClearFailUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCheckPointWidget> ShowMapNameWidget_BP;

	UPROPERTY()
	class UCheckPointWidget* ShowMapNameWidget;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> cc_BP;

	UPROPERTY()
	int32 playerCount;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(Replicated)
	float clearTime = 180;

	UPROPERTY(Replicated)
	bool bDungeonLoaded = false;

	bool bPlayerCount = true;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuffDebuffManager> BuffDebuffManagerClass;

	UPROPERTY()
	class ABuffDebuffManager* BuffDebuffManagers;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class ULoadingWidget> sLoadingUI_BP;

	UPROPERTY()
	class ULoadingWidget* sLoadingUI;
};
