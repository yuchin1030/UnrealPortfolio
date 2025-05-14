// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OurGameStateBase.generated.h"

DECLARE_DELEGATE(FLoadingEnd);

/**
 * 
 */
UCLASS()
class CHALLENGERS_API AOurGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AOurGameStateBase();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	FLoadingEnd loadingEndDelegate;

	class AOurGameModeBase* gm;

	class AMainPlayerController* pc;

	class UOurGameInstance* gi;

	class AChallengersCharacter* cc;

	UPROPERTY(Replicated)
	int32 ClearWidget_Cost=0;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool bisDunLoad;

	UPROPERTY(Replicated)
	bool _bisDunLoadStart;

	UPROPERTY(Replicated)
	float _cleatTimer;

	UPROPERTY(Replicated)
	bool bisMulti;

	UPROPERTY(Replicated)
	bool bisDun;

	UPROPERTY(Replicated)
	bool _bisSteam;

	UPROPERTY(Replicated)
	bool _bisCyber;

	UPROPERTY(Replicated)
	int32 _enemyTotal;

	UPROPERTY(Replicated)
	int32 _enemyCurrent;

	UPROPERTY(Replicated)
	int32 _playerCount;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UEnemyCountInDungeonWidget> enemyCountUI_BP;

	UPROPERTY()
	class UEnemyCountInDungeonWidget* enemyCountUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UDungeonClearFailWidget> dungeonClearFail_BP;

	UPROPERTY()
	class UDungeonClearFailWidget* dungeonClearFailUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class ULoadingWidget> loadingUI_BP;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	class ULoadingWidget* loadingUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCheckPointWidget> ShowMapNameWidget_BP;

	UPROPERTY()
	class UCheckPointWidget* ShowMapNameWidget;

	bool Test;

	UPROPERTY(Replicated)
	bool _bDungeonFinished;

	bool bisFailedUI = false;

	bool bIsLoadingEndCheak1 = false;

	bool bIsLoadingEndCheak2 = false;

	UFUNCTION()
	void ISDungeonFinished();

	UFUNCTION()
	void ClearFailed();

	// ---------------À¯Áø---------------
	UFUNCTION(Server, Reliable)
	void ServerRPC_EXP();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_EXP();
};
