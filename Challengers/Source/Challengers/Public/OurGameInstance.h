// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "CHR/BaseEnemy.h"
#include "CHR/EnemySaveData.h"
#include "Yuchin/SkillPresetSaveData.h"
#include "Yohan/SaveDungeonData.h"
#include "Yuchin/PlayerInfoSaveData.h"
#include "OurGameInstance.generated.h"

DECLARE_DELEGATE(FLoadingEnd);
DECLARE_DELEGATE_OneParam(FCreateRoom, bool bIsSucceed);

/**
 * 
 */
 USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString roomName;
	UPROPERTY(BlueprintReadOnly)
	FString hostName;
	UPROPERTY(BlueprintReadOnly)
	FString userName;
	UPROPERTY(BlueprintReadOnly)
	int32 currentPlayerCount;

	int32 index;

	FORCEINLINE void Set(int32 _index, const FOnlineSessionSearchResult& item) {
		index = _index;
		//item.Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
		//item.Session.SessionSettings.Get(FName("HOST_NAME"), hostName);
		// 방장의 이름
		userName = item.Session.OwningUserName;
		// 현재 방에 들어온 플레이어 수
		currentPlayerCount = 4 - item.Session.NumOpenPublicConnections;
	}

};

 // 방찾기 요청 후 응답이 왔을 때 호출될 델리게이트
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessioinSearchDelegate, const FSessionInfo&, info);
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessioinSearchFinishedDelegate, bool, bSearching);

UCLASS()
class CHALLENGERS_API UOurGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	virtual void Init() override;
	
public:
	const UDataTable* DT_BodyData = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/CHR/Data/DT_EnemyBodySpec.DT_EnemyBodySpec'"));

	const UDataTable* DT_Weapon1Data = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/CHR/Data/DT_EnemyOneHandWeaponSpec.DT_EnemyOneHandWeaponSpec'"));
	
	const UDataTable* DT_Weapon2Data = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/CHR/Data/DT_EnemyTwoHandWeaponSpec.DT_EnemyTwoHandWeaponSpec'"));
	
	const UDataTable* DT_GearData = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/CHR/Data/DT_EnemyGearSpec.DT_EnemyGearSpec'"));

	const UDataTable* DT_SkillInfo = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Yuchin/Skills/DT_SkillsInfo.DT_SkillsInfo'"));

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FEnemySaveDataStruct> loadedEnemyDataList;

	//에너미 저장 파일을 생성한다.
	UFUNCTION(BlueprintCallable)
	void CreateEnemySaveFile();
	//에너미 데이터를 저장한다.
	UFUNCTION(BlueprintCallable)
	void SaveEnemyData(FString _name, bool _bIsBossType, int32 _totalCost, FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName, struct FAIStat _AIData);
	//에너미 데이터를 로드한다.
	UFUNCTION(BlueprintCallable)
	void LoadEnemyData();


	UPROPERTY()
	bool LoadbIsMan;
	UPROPERTY()
	TArray<FName> LoadFinalMeshArr;
	UPROPERTY()
	FString LoadPlayerName;
	UPROPERTY()
	int LoadClothesColorNumber;
	UPROPERTY()
	int LoadHairColorNumber;
	UPROPERTY()
	int LoadGloveNum;
	UPROPERTY()
	bool LoadbGlove;


	// 던전 에디터 UI 생성
	UPROPERTY(EditDefaultsOnly, Category  = "UI")
	TSubclassOf<class UUserWidget> dungeonEditUI_BP;

	class UDungeonEditWidget* dungeonEditUI;

	
	void CreateSaveCharacterCustom();
	
	void SaveChracterCustom(bool _bIsMan, TArray<FName> __FinalMeshArr, FString __PlayerName,int __ClothesColorNum, int __HairColorNum , bool _bGlove);

	void LoadChacraterCustom();

/////////////////// 유진 /////////////////////////// 

	// 스킬 프리셋 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FSkillPresetSaveDataStruct loadedSkillDataList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 loadedCurrentSkillPoint;

	UFUNCTION(BlueprintCallable)
	void CreateSkillPresetSaveFile();

	UFUNCTION(BlueprintCallable)
	void SaveSkillPresetData(FString _playerName,TArray<int32> _skillPointArr, int32 _CurrentSkillPoint);

	UFUNCTION(BlueprintCallable)
	void LoadSkillPresetData();

	// 플레이어 정보 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FPlayerInfoSaveDataStruct loadedPlayerInfoDataList;

	UFUNCTION(BlueprintCallable)
	void CreatePlayerInfoSaveFile();

	UFUNCTION(BlueprintCallable)
	void SavePlayerInfoData(FString _playerName, int32 _playerLevel, int32 _playerGold, int32 _playerCurrentExp, int32 _playerMaxExp, int32 _playerEnemyCost, TArray<int32> _weaponLevel, TArray<int32> _currentWeaponStat, TArray<int32> _nextWeaponStat, TArray<int32> _upgWeaponNeedGold);

	UFUNCTION(BlueprintCallable)
	void LoadPlayerInfoData();

	UPROPERTY()
	float swordDamage = 1;

	UPROPERTY()
	float wandDamage = 1;

	UPROPERTY()
	float bowDamage = 1;

	UPROPERTY()
	float buffSwordDamagePercent = 1;

	UPROPERTY()
	float buffWandDamagePercent = 1;

	UPROPERTY()
	float buffBowDamagePercent = 1;

/////////////////// 요한 /////////////////////////// 
	UPROPERTY()
	int32 _enemyCost;

	UPROPERTY()
	TArray<FDunInfo> loadedDunData;

	UPROPERTY()
	int32 createDunCost;

	UPROPERTY()
	FString createDunName;

	UPROPERTY()
	FString createDunType;

	UPROPERTY()
	FString CurrentMapName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALevelPlace> startLoc_BP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseEnemy> enemy_BP;

	UPROPERTY()
	bool isDungeonLoaded = false;

	UPROPERTY()
	bool bdunloadStart;

	UPROPERTY(BlueprintReadWrite)
	bool bSLoading;

	UPROPERTY()
	bool bisMulti;

	UPROPERTY()
	bool bisDun;

	UPROPERTY()
	bool bisSteam;

	UPROPERTY()
	bool bisCyber;

	FString playerName;

	UFUNCTION()
	void SaveDungeon(FString _dunName, FString _dunType);
	
	UFUNCTION()
	void LoadDungeonData();

	UFUNCTION()
	void LoadDungeon(FString _dunName, FString _dunType);

	UFUNCTION()
	void RemoveDungeon(FString _dunName);

	UFUNCTION()
	void RemoveEnemy(FString _name);

	UFUNCTION()
	void MoveToDungeon();

	UFUNCTION()
	void MapLoaded();

	UFUNCTION()
	void LoadPlayData();
	
	UFUNCTION()
	bool IsServer();

	FLoadingEnd loadingEndDelegate;
	
	FCreateRoom createRoomDelegate;

	///////////////////////
	// 네트워크 방만들기 //
	///////////////////////

	UPROPERTY(EditDefaultsOnly)
	int32 maxPlayerPerRoom = 4;


	IOnlineSessionPtr sessionInterface;

	FSessioinSearchDelegate OnMySessionSearchCompleteDelegate;

	FSessioinSearchFinishedDelegate OnMySessionSearchFinishedDelegate;

	FString mySessionName = TEXT("SeaMonKi");

	TSharedPtr<FOnlineSessionSearch> sessionInSearch;

	void CreateMySession(FString roomName);

	UFUNCTION()
	void OnCreateSessionComplete(FName sessionName, bool bWasSuccessful);

	void FindOtherSessions();

	UFUNCTION()
	void OnFindSessionComplete(bool bWasSuccessful);

	void JoinMySession(int32 index);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result);

	FString StringBase64Encode(const FString& str);
	FString StringBase64Decode(const FString& str);
};
