// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CHR/BaseEnemy.h"
#include "TestRoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ATestRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATestRoomGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class AChallengersCharacter* playerREF;
	
	class ABaseEnemy* enemyREF;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseEnemy> enemy_BP;

	class ADrawRangeActor* rangeActor;

	class ATargetPoint* spawnPoint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName bodyRowName = FName("NB1");//몸체의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon1RowName = FName("W1_0");//장비1의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon2RowName = FName("W2_0");//장비2의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName gearRowName = FName("0");//특수능력의 RowName

	struct FAIStat AIData;//AI데이터 구조체

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> damageType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTestRoomAIWidget> AIWidget_bp;

	class UTestRoomAIWidget* AIWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTestRoomSetWidget> SetWidget_bp;

	class UTestRoomSetWidget* SetWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTestRoomSaveWidget> SaveWidget_bp;

	class UTestRoomSaveWidget* SaveWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTestRoomLoadWidget> LoadWidget_bp;

	class UTestRoomLoadWidget* LoadWidget;

	bool bIsRotate = false;

	bool bIsBack = false;

	FTimerHandle rotateTimer;

	FString currentEnemyName = "";

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULoadingWidget> loadingUI_BP;

	UPROPERTY()
	class ULoadingWidget* loadingUI;

	void RotateEnemy(bool _bIsBack);

	void DestroyEnemy();

	void SpawnEnemy();

	void ShowAIUI();

	void ShowSettingUI();

	void ShowSaveUI();

	void ShowLoadUI();

	void SetEnemySetting(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName);

	void SetAI(struct FAIStat _AIData);
};
