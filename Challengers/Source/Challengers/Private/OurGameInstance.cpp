// Fill out your copyright notice in the Description page of Project Settings.


#include "OurGameInstance.h"
#include "CHR/BaseEnemy.h"
#include "GJY/CustomCharacterSave.h"
#include "Kismet/GamePlayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystem.h"
#include "string"
#include "Yohan/DungeonEditWidget.h"
#include "Yohan/SaveDungeonData.h"
#include "Yuchin/SkillPresetSaveData.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include <ChallengersCharacter.h>
#include <Yohan/LevelPlace.h>
#include <Engine/LevelStreamingDynamic.h>
#include <OurGameModeBase.h>
#include "Yohan/EnemyCountInDungeonWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DirectionalLight.h>
#include <../../../../../../../Source/Runtime/Engine/Public/Net/UnrealNetwork.h>
#include "Yohan/DungeonEditGameModeBase.h"
#include "Yuchin/PlayerInfoSaveData.h"
#include "Yohan/OurGameStateBase.h"


void UOurGameInstance::Init()
{
	Super::Init();

	auto subsys = IOnlineSubsystem::Get();
	if (subsys) {
		sessionInterface = subsys->GetSessionInterface();

		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOurGameInstance::OnCreateSessionComplete);
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOurGameInstance::OnFindSessionComplete);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UOurGameInstance::OnJoinSessionComplete);
	}	
}


bool UOurGameInstance::IsServer()
{
	if (GetWorld())
	{
		ENetMode NetMode = GetWorld()->GetNetMode();
		return NetMode == NM_ListenServer || NetMode == NM_DedicatedServer;
	}
	return false;
}



void UOurGameInstance::CreateEnemySaveFile()
{
	UEnemySaveData* dataToSave = Cast<UEnemySaveData>(UGameplayStatics::CreateSaveGameObject(UEnemySaveData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(dataToSave, "EnemyData", 0);
}

void UOurGameInstance::SaveEnemyData(FString _name, bool _bIsBossType, int32 _totalCost, FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName, struct FAIStat _AIData)
{
	if (!UGameplayStatics::DoesSaveGameExist("EnemyData", 0)) {
		CreateEnemySaveFile();
	}

	UEnemySaveData* dataToSave = Cast<UEnemySaveData>(UGameplayStatics::LoadGameFromSlot("EnemyData", 0));

	if (dataToSave)
	{
		//세이브 데이터 저장
		for (int32 i = 0; i < dataToSave->enemyDataList.Num(); i++) {
			//같은 이름의 에너미가 저장되 있는 경우.
			if (dataToSave->enemyDataList[i].name == _name) {
				dataToSave->enemyDataList[i].bIsBossType = _bIsBossType;
				dataToSave->enemyDataList[i].totalCost = _totalCost;
				dataToSave->enemyDataList[i].bodyRowName = _bodyRowName;
				dataToSave->enemyDataList[i].weapon1RowName = _weapon1RowName;
				dataToSave->enemyDataList[i].weapon2RowName = _weapon2RowName;
				dataToSave->enemyDataList[i].gearRowName = _gearRowName;
				dataToSave->enemyDataList[i].AIData = _AIData;
				UGameplayStatics::SaveGameToSlot(dataToSave, "EnemyData", 0);
				return;
			}
		}
		//같은 이름의 에너미가 없으므로 새로 저장한다.
		FEnemySaveDataStruct newSaveData;
		newSaveData.name = _name;
		newSaveData.bIsBossType = _bIsBossType;
		newSaveData.totalCost = _totalCost;
		newSaveData.bodyRowName = _bodyRowName;
		newSaveData.weapon1RowName = _weapon1RowName;
		newSaveData.weapon2RowName = _weapon2RowName;
		newSaveData.gearRowName = _gearRowName;
		newSaveData.AIData = _AIData;
		
		dataToSave->enemyDataList.Add(newSaveData);
		UGameplayStatics::SaveGameToSlot(dataToSave, "EnemyData", 0);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("Save Error!!!"));
	}
	return;
}

void UOurGameInstance::LoadEnemyData()
{
	if (!UGameplayStatics::DoesSaveGameExist("EnemyData", 0)) {
		CreateEnemySaveFile();
	}

	UEnemySaveData* dataToLoad = Cast<UEnemySaveData>(UGameplayStatics::LoadGameFromSlot("EnemyData", 0));

	if (dataToLoad) {
		loadedEnemyDataList = dataToLoad->enemyDataList;
	}
}

void UOurGameInstance::CreateSaveCharacterCustom()
{
	UCustomCharacterSave* CharacterSave = Cast<UCustomCharacterSave>(UGameplayStatics::CreateSaveGameObject(UCustomCharacterSave::StaticClass()));
	UGameplayStatics::SaveGameToSlot(CharacterSave, "CustomCharacter",0);
}

void UOurGameInstance::SaveChracterCustom(bool _bIsMan, TArray<FName> __FinalMeshArry , FString __PlayerName, int __ClothesColorNum, int __HairColorNum, bool _bGlove)
{
	if(!UGameplayStatics::DoesSaveGameExist("CustomCharacter",0))
	{
		CreateSaveCharacterCustom();;
	}

	UCustomCharacterSave* CharacterSave = Cast<UCustomCharacterSave>(UGameplayStatics::LoadGameFromSlot("CustomCharacter",0));

	if(CharacterSave)
	{
		CharacterSave->bIsMan =_bIsMan;

		CharacterSave->_FinalMeshArr = __FinalMeshArry;

		CharacterSave->playerName = __PlayerName;

		CharacterSave->_ClothesColorNum = __ClothesColorNum;

		CharacterSave->_HairColorNum = __HairColorNum;

		CharacterSave->bGlove = _bGlove;
	}
	UGameplayStatics::SaveGameToSlot(CharacterSave, "CustomCharacter",0);
}

void UOurGameInstance::LoadChacraterCustom()
{
	UCustomCharacterSave* CharacterLoad = Cast<UCustomCharacterSave>(UGameplayStatics::LoadGameFromSlot("CustomCharacter",0));
	if(CharacterLoad)
	{
		LoadbIsMan = CharacterLoad->bIsMan;
		LoadFinalMeshArr = CharacterLoad->_FinalMeshArr;
		LoadPlayerName = CharacterLoad->playerName;
		LoadClothesColorNumber = CharacterLoad->_ClothesColorNum;
		LoadHairColorNumber = CharacterLoad->_HairColorNum;
		LoadbGlove = CharacterLoad->bGlove;

	}
	else if (!UGameplayStatics::DoesSaveGameExist("CustomCharacter", 0)) {
		CreateSaveCharacterCustom();

		CharacterLoad = Cast<UCustomCharacterSave>(UGameplayStatics::LoadGameFromSlot("CustomCharacter", 0));

		LoadbIsMan = CharacterLoad->bIsMan;
		LoadFinalMeshArr = CharacterLoad->_FinalMeshArr;
		LoadPlayerName = CharacterLoad->playerName;
		LoadClothesColorNumber = CharacterLoad->_ClothesColorNum;
		LoadHairColorNumber = CharacterLoad->_HairColorNum;
	}

}

void UOurGameInstance::CreateSkillPresetSaveFile()
{
	USkillPresetSaveData* skillDataToSave = Cast<USkillPresetSaveData>(UGameplayStatics::CreateSaveGameObject(USkillPresetSaveData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(skillDataToSave, "SkillPresetData", 0);
}

void UOurGameInstance::SaveSkillPresetData(FString _playerName, TArray<int32> _skillPointArr, int32 _CurrentSkillPoint)
{
	// 처음에 스킬 프리셋 데이터가 존재하지 않으면 생성한다.
	if (!UGameplayStatics::DoesSaveGameExist("SkillPresetData", 0))
	{
		CreateSkillPresetSaveFile();
	}

	// 저장된 데이터가 있다면 로드한다.
	USkillPresetSaveData* skillDataToSave = Cast<USkillPresetSaveData>(UGameplayStatics::LoadGameFromSlot("SkillPresetData", 0));

	if (skillDataToSave)
	{
		//for (int32 i = 1; i <= skillDataToSave->skillDataList.Num() - 1; i++)
		//{
		//	// 있는 플레이어 이름이라면
		//	if (skillDataToSave->skillDataList[i].playerName == _playerName)
		//	{
		//		// 저장하려고하는 데이터의 스킬포인트 배열에 입력받는 배열 값 저장
		//		skillDataToSave->skillDataList[i].playerName = _playerName;
		//		skillDataToSave->skillDataList[i].skillPointArr = _skillPointArr;
		//		skillDataToSave->skillDataList[i].canUseSkillPoint = _CurrentSkillPoint;

		//		UGameplayStatics::SaveGameToSlot(skillDataToSave, "SkillPresetData", 0);
		//		return;
		//	}
		//}
		//같은 이름의 플레이어가 없으므로 새로 저장한다.
		FSkillPresetSaveDataStruct newSaveData;
		newSaveData.playerName = _playerName;
		newSaveData.skillPointArr = _skillPointArr;
		newSaveData.canUseSkillPoint = _CurrentSkillPoint;

		skillDataToSave->skillDataList = newSaveData;
		UGameplayStatics::SaveGameToSlot(skillDataToSave, "SkillPresetData", 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SkillData Save Error"));
	}
	return;
}

void UOurGameInstance::LoadSkillPresetData()
{
	if (!UGameplayStatics::DoesSaveGameExist("SkillPresetData", 0))
	{
		CreateSkillPresetSaveFile();
	}

	USkillPresetSaveData* skillDataToLoad = Cast<USkillPresetSaveData>(UGameplayStatics::LoadGameFromSlot("SkillPresetData", 0));

	if (skillDataToLoad)
	{
		loadedSkillDataList = skillDataToLoad->skillDataList;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SkillData Load Error"));
	}
	return;
}

void UOurGameInstance::CreatePlayerInfoSaveFile()
{
	UPlayerInfoSaveData* playerInfoDataToSave = Cast<UPlayerInfoSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerInfoSaveData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(playerInfoDataToSave, "PlayerInfoData", 0);
}

void UOurGameInstance::SavePlayerInfoData(FString _playerName, int32 _playerLevel, int32 _playerGold, int32 _playerCurrentExp, int32 _playerMaxExp, int32 _playerEnemyCost, TArray<int32> _weaponLevel, TArray<int32> _currentWeaponStat, TArray<int32> _nextWeaponStat, TArray<int32> _upgWeaponNeedGold)
{
	if (!UGameplayStatics::DoesSaveGameExist("PlayerInfoData", 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Create in Load"));
		CreatePlayerInfoSaveFile();
	}

	UPlayerInfoSaveData* dataToSave = Cast<UPlayerInfoSaveData>(UGameplayStatics::LoadGameFromSlot("PlayerInfoData", 0));

	if (dataToSave)
	{
		//세이브 데이터 저장
		//for (int32 i = 1; i <= dataToSave->playerInfoDataList.Num() - 1; i++) {
		//	//같은 이름의 플레이어가 저장되어 있는 경우.
		//	if (dataToSave->playerInfoDataList[i].playerName == _playerName) {
		//		dataToSave->playerInfoDataList[i].playerLevel = _playerLevel;
		//		dataToSave->playerInfoDataList[i].playerGold = _playerGold;
		//		dataToSave->playerInfoDataList[i].playerCurrentExp = _playerCurrentExp;
		//		dataToSave->playerInfoDataList[i].playerMaxExp = _playerMaxExp;
		//		dataToSave->playerInfoDataList[i].playerEnemyCost = _playerEnemyCost;
		//		dataToSave->playerInfoDataList[i].weaponLevel = _weaponLevel;
		//		dataToSave->playerInfoDataList[i].currentWeaponStat = _currentWeaponStat;
		//		dataToSave->playerInfoDataList[i].upgWeaponNeedGold = _upgWeaponNeedGold;
		//		UE_LOG(LogTemp, Warning, TEXT("Save [%d] Gold : %d / %d"), i, dataToSave->playerInfoDataList[i].playerGold, _playerGold);
		//		UGameplayStatics::SaveGameToSlot(dataToSave, "PlayerInfoData", 0);
		//		return;
		//	}
		//}

		//같은 이름의 플레이어가 없으므로 새로 저장한다.
		FPlayerInfoSaveDataStruct newSaveData;
		newSaveData.playerName = _playerName;
		newSaveData.playerLevel = _playerLevel;
		newSaveData.playerGold = _playerGold;
		newSaveData.playerCurrentExp = _playerCurrentExp;
		newSaveData.playerMaxExp = _playerMaxExp;
		newSaveData.playerEnemyCost = _playerEnemyCost;
		newSaveData.weaponLevel = _weaponLevel;
		newSaveData.currentWeaponStat = _currentWeaponStat;
		newSaveData.nextWeaponStat = _nextWeaponStat;
		newSaveData.upgWeaponNeedGold = _upgWeaponNeedGold;

		dataToSave->playerInfoDataList = newSaveData;
		UGameplayStatics::SaveGameToSlot(dataToSave, "PlayerInfoData", 0);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerInfo Save Error"));
	}
	return;
}

void UOurGameInstance::LoadPlayerInfoData()
{
	if (!UGameplayStatics::DoesSaveGameExist("PlayerInfoData", 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Create in Load"));
		CreatePlayerInfoSaveFile();
	}

	UPlayerInfoSaveData* playerInfoDataToLoad = Cast<UPlayerInfoSaveData>(UGameplayStatics::LoadGameFromSlot("PlayerInfoData", 0));

	if (playerInfoDataToLoad)
	{
		loadedPlayerInfoDataList = playerInfoDataToLoad->playerInfoDataList;
		UE_LOG(LogTemp, Warning, TEXT("LoadPlayerInfo111111"));

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInfo Load Error"));
	}
	return;
}

void UOurGameInstance::SaveDungeon(FString _dunName, FString _dunType)
{
	// 기존 데이터를 로드
	USaveDungeonData* sD;
	// 저장된 데이터가 있다면 로드한다
	if (UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot"), 0))
	{
		sD = Cast<USaveDungeonData>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
	}
	//없으면 새로 만든다
	else
	{
		sD = Cast<USaveDungeonData>(UGameplayStatics::CreateSaveGameObject(USaveDungeonData::StaticClass()));
	}

	if (!sD) return;

	FObjectSaveData saveData;
	
	// 같은 이름을 가진 던전의 존재 판별
	bool bDungeonExists = false;

	// 기존 던전 데이터 업데이트
	for (int i = 0; i < sD->dunInfos.Num(); i++)
	{
		// 같은 이름을 가진 던전이 있다면
		if (sD->dunInfos[i].dunName == _dunName)
		{
			// enmey 배열을 비운다
			sD->dunInfos[i].savedEnemys.Empty();
			
			sD->dunInfos[i].dunTotalCost = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode())->curEnemyCost;
			// 월드에 배치된 enemy들을 찾아서 배열에 담는다
			for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
			{
				ABaseEnemy* saveEnemy = *it;
				if (saveEnemy)
				{
					saveData.enemyClass = saveEnemy->GetClass()->GetPathName();
					saveData.bodyRow = saveEnemy->bodyRowName;
					saveData.weaponRow1 = saveEnemy->weapon1RowName;
					saveData.weaponRow2 = saveEnemy->weapon2RowName;
					saveData.gearRow = saveEnemy->gearRowName;
					saveData.aiDT = saveEnemy->AIData;
					saveData.Location = saveEnemy->GetActorLocation();
					saveData.Rotation = saveEnemy->GetActorRotation();
					
					sD->dunInfos[i].savedEnemys.Add(saveData);
					
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("Updating existing dungeon: %s"), *sD->dunInfos[i].dunName);
			
			// 같은 이름을 가진 던전 판별을 True로 바꾼다
			bDungeonExists = true;
			break;
		}
	}

	// 새로운 던전 데이터 추가
	// 같은 이름을 가진 던전이 없다면
	if (!bDungeonExists)
	{
		// 새로운 enemy 배열을 만든다
		TArray<FObjectSaveData> newEnemyList;
		
		// 월드에 존재하는 enemy를 찾아서 배열에 정보를 넣는다
		for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
		{
			ABaseEnemy* saveEnemy = *it;
			if (saveEnemy)
			{
				saveData.enemyClass = saveEnemy->GetClass()->GetPathName();
				saveData.bodyRow = saveEnemy->bodyRowName;
				saveData.weaponRow1 = saveEnemy->weapon1RowName;
				saveData.weaponRow2 = saveEnemy->weapon2RowName;
				saveData.gearRow = saveEnemy->gearRowName;
				saveData.aiDT = saveEnemy->AIData;
				saveData.Location = saveEnemy->GetActorLocation();
				saveData.Rotation = saveEnemy->GetActorRotation();

				newEnemyList.Add(saveData);
			}
		}
		// 던전 정보를 저장하는 구조체에 정보를 넣어준다
		FDunInfo newDunInfo;
		newDunInfo.dunName = _dunName;
		newDunInfo.dunType = _dunType;
		newDunInfo.savedEnemys = newEnemyList;	
		newDunInfo.dunTotalCost = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode())->curEnemyCost;
		sD->dunInfos.Add(newDunInfo);

		UE_LOG(LogTemp, Warning, TEXT("Saving new dungeon: %s"), *newDunInfo.dunName);
	}

	// 데이터를 저장
	UGameplayStatics::SaveGameToSlot(sD, TEXT("SaveSlot"), 0);
}

void UOurGameInstance::LoadDungeonData()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot"), 0))
	{
		USaveDungeonData* LoadedGame = Cast<USaveDungeonData>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
		if (LoadedGame)
		{
			loadedDunData = LoadedGame->dunInfos;
			UE_LOG(LogTemp, Warning, TEXT("Loaded %d dungeons"), loadedDunData.Num());
			for (int i = 0; i < loadedDunData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Dungeon: %s"), *loadedDunData[i].dunName);
				UE_LOG(LogTemp, Warning, TEXT("Dungeon: %s"), *loadedDunData[i].dunType);
			}
		}
	}
}

void UOurGameInstance::LoadDungeon(FString _dunName, FString _dunType)
{
	auto gm = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!UGameplayStatics::DoesSaveGameExist("SaveSlot", 0))
	{
		SaveDungeon(_dunName, _dunType);
	}
	USaveDungeonData* lD = Cast<USaveDungeonData>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
	if (lD)
	{
		// 기존에 스폰되어 있는 enemy를 파괴한다
		for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
		{
			it->Died(false);

			if (GetWorld()->GetName() == "DungeonEditMap")
			{
				gm->curEnemyCost = gm->curEnemyCost - it->enemySpec.totalCost;
			}
		}

		// 던전 데이터를 로드한다
		for (int i = 0; i < lD->dunInfos.Num(); i++)
		{
			if (lD->dunInfos[i].dunName == _dunName)
			{
				for (const FObjectSaveData& SaveData : lD->dunInfos[i].savedEnemys)
				{
					UClass* newEnemyClass = LoadObject<UClass>(nullptr, *SaveData.enemyClass);

					if (newEnemyClass)
					{
						FActorSpawnParameters spawnParams;
						ABaseEnemy* newEnemy = GetWorld()->SpawnActor<ABaseEnemy>(newEnemyClass, SaveData.Location, SaveData.Rotation, spawnParams);

						newEnemy->LoadData(SaveData.bodyRow, SaveData.weaponRow1, SaveData.weaponRow2, SaveData.gearRow, SaveData.aiDT);

						if (GetWorld()->GetName() == "DungeonEditMap")
						{
							gm->curEnemyCost = gm->curEnemyCost + newEnemy->enemySpec.totalCost;

						}
					}

				}
			}
			
		}
		
	}
}

void UOurGameInstance::RemoveDungeon(FString _dunName)
{
	// 저장되어 있는 던전 데이터 가져오기
	USaveDungeonData* sD;
	if(UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot"), 0))
	{
		sD = Cast<USaveDungeonData>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
	}
	else
	{
		return;
	}

	// 던전 데이터 삭제
	for (int i = 0; i < sD->dunInfos.Num(); i++)
	{
		// 던전의 이름이 같다면
		if (sD->dunInfos[i].dunName == _dunName)
		{
			// 던전 데이터를 dunInfo에서 삭제
			sD->dunInfos.RemoveAt(i);
			
			break;
		}
	}
	// 새로 데이터 저장
	UGameplayStatics::SaveGameToSlot(sD, TEXT("SaveSlot"), 0);
}


void UOurGameInstance::RemoveEnemy(FString _name)
{
	// 저장되어 있는 에너미 데이터 가져오기
	UEnemySaveData* eD = nullptr;
	
	if(UGameplayStatics::DoesSaveGameExist(TEXT("EnemyData"), 0))
	{
		eD = Cast<UEnemySaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("EnemyData"), 0));
	}
	
	for (int i = 0; i < eD->enemyDataList.Num(); i++)
	{
		// 삭제요청한 에너미의 이름이 있다면, 그 인덱스를 지운다
		if (eD->enemyDataList[i].name == _name)
		{
			eD->enemyDataList.RemoveAt(i);

			break;
		}
	}
	// 새로 데이터 저장
	UGameplayStatics::SaveGameToSlot(eD, TEXT("EnemyData"), 0 );
}

void UOurGameInstance::MoveToDungeon()
{
	// 현재 맵 이름 저장
	CurrentMapName = GetWorld()->GetName();

	// 서버에서만 하게 한다
	if (IsServer())
	{
		auto gs = Cast<AOurGameStateBase>(GetWorld()->GetGameState());

		if (CurrentMapName == "DungeonPlayMap")
		{
			// 서버트레블 할 때 로딩화면 띄우기
			bdunloadStart = true;
			bisMulti = true;
			GetWorld()->ServerTravel(TEXT("/Game/Gothic_Cathedral/Maps/MultipMap?listen"));
			
			FTimerHandle tiner;
			GetWorld()->GetTimerManager().SetTimer(tiner, [&] {
				bdunloadStart = false;
				if (loadingEndDelegate.IsBound()) {
					loadingEndDelegate.Execute();

				}
			}, 8, false);
			
				
		
		}
		else if (CurrentMapName != "DungeonPlayMap")
		{
			// 플레이할 던전으로 서버 트레블한다
			GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/DungeonPlayMap?listen"));
			
			bdunloadStart = true;
			
			if (createDunType == "Steam Punk")
			{
				bisSteam = true;
			}
			else if (createDunType == "Diesel Punk")
			{
				bisDun = true;
			}
			else
			{
				bisCyber = true;
			}
			

			FTimerHandle t;
			GetWorld()->GetTimerManager().SetTimer(t, [&] {
				MapLoaded();
			
				}, 7, false);
							
		}
	}
	
	
}

void UOurGameInstance::MapLoaded()
{	
	
		if (IsServer())
		{			
			// 현재의 맵 위치한 맵이 플레이 맵이라면
			// 던전 타입에 맞는 던전을 로드한다
			CurrentMapName = GetWorld()->GetName();
			if (CurrentMapName == "DungeonPlayMap")
			{
				//bool bOutSuccess;

				FVector levLocation = FVector(0, 0, 0);

				if (createDunType == "Steam Punk")
				{
					FLatentActionInfo latentInfo;

					// 레벨 로드되고 나서 델리게이트 거는 부분
					latentInfo.CallbackTarget = this;
					latentInfo.ExecutionFunction = FName(TEXT("LoadPlayData"));
					latentInfo.Linkage = 0;

					UGameplayStatics::LoadStreamLevel(GetWorld(), FName("Airship"), true, false, latentInfo);
				}
				else if (createDunType == "Diesel Punk")
				{					
					FLatentActionInfo latentInfo;
					
					// 레벨 로드되고 나서 델리게이트 거는 부분
					latentInfo.CallbackTarget = this;
					latentInfo.ExecutionFunction = FName(TEXT("LoadPlayData"));
					latentInfo.Linkage = 0;
					
					UGameplayStatics::LoadStreamLevel(GetWorld(), FName("DisselPunk"), true, false, latentInfo);					
				}
				else if (createDunType == "Cyber Punk")
				{
					FLatentActionInfo latentInfo;

					// 레벨 로드되고 나서 델리게이트 거는 부분
					latentInfo.CallbackTarget = this;
					latentInfo.ExecutionFunction = FName(TEXT("LoadPlayData"));
					latentInfo.Linkage = 0;

					UGameplayStatics::LoadStreamLevel(GetWorld(), FName("CyberPunk01"), true, false, latentInfo);
				}
			}
		}			
}



void UOurGameInstance::LoadPlayData()
{
	
	if (IsServer())
	{
		FTimerHandle timer;

		// 3초뒤에 캐릭터의 위치를 시작 지점으로 고정한다.
		// 바로 하면, 로드 완료 전이라 시작 지점을 인식 못함
		GetWorld()->GetTimerManager().SetTimer(timer, [&]() {
			
			for (TActorIterator<AChallengersCharacter> It(GetWorld()); It; ++It)
			{
				auto cc = *It;

				if (cc)
				{
					TArray<AActor*> actorArray;

					UGameplayStatics::GetAllActorsOfClass(GetWorld(), startLoc_BP, actorArray);

					if (actorArray.Num() > 0)
					{
						// 시작지점 찾아서 위치 이동
						cc->SetActorLocation(actorArray[0]->GetActorLocation());
						cc->SetActorRotation(actorArray[0]->GetActorRotation());
					}
				}
			}

			// 던전데이터를 로드한다
			LoadDungeon(createDunName, createDunType);

			// 현재 맵에 존재하는 enemy 갯수 불러오기
			TArray<AActor*> enemysArray;

			UGameplayStatics::GetAllActorsOfClass(GetWorld(), enemy_BP, enemysArray);

			// 게임 모드 불러옴
			auto gm = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
			
			// 현재 레벨에 로드된 enemy를 다 불러와서, 게임모드의 enemyTotal에 부여함
			if (gm)
			{
				// 게임모드에 총 몬스터 수 / 현재 몬스터 수를 저장한다
				gm->enemyTotal = enemysArray.Num();
				gm->enemyCurrent = gm->enemyTotal;
				// 던전 로드 됐음을 알려줌
				gm->bDungeonLoaded = true;
			}			
		}, 7, false);			
	}
}


void UOurGameInstance::CreateMySession(FString roomName)
{
	FOnlineSessionSettings set;

	set.bIsDedicated = false;
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	set.bIsLANMatch = subsysName == "NULL";
	set.bShouldAdvertise = true;
	set.bUsesPresence = true;
	set.bAllowJoinInProgress = true;
	set.bAllowJoinViaPresence = false;
	set.NumPublicConnections = maxPlayerPerRoom;

	set.Set(FName("ROOM_NAME"), StringBase64Encode(roomName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	set.Set(FName("HOST_NAME"), StringBase64Encode(mySessionName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	sessionInterface->CreateSession(*netID, FName(*roomName), set);
}

void UOurGameInstance::OnCreateSessionComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete -> sessionName : %s, bWasSuccessful : %d"), *sessionName.ToString(), bWasSuccessful);

	// 만약 방생성을 성공했다면 ServerTravel 하고싶다.
	if (bWasSuccessful)
	{
		if (createRoomDelegate.IsBound()) {
			createRoomDelegate.Execute(true);
		}

		FTimerHandle fadeOutTimer;
		GetWorld()->GetTimerManager().SetTimer(fadeOutTimer, [&] {
			// 로딩창 띄우기
			bdunloadStart = true;

			// 멀티맵 로딩창
			bisMulti = true;

			GetWorld()->ServerTravel(TEXT("/Game/Gothic_Cathedral/Maps/MultipMap?listen"));
		}, 1.0f, false);


		// 5초뒤에 로딩창 끄기
		FTimerHandle tiner;
		GetWorld()->GetTimerManager().SetTimer(tiner, [&] {
		bdunloadStart = false;
		if (loadingEndDelegate.IsBound()) {
			loadingEndDelegate.Execute();
		}
		}, 7, false);
	}
	else {
		if (createRoomDelegate.IsBound()) {
			createRoomDelegate.Execute(false);
		}
	}
}

void UOurGameInstance::FindOtherSessions()
{
	if (OnMySessionSearchFinishedDelegate.IsBound()) {
		OnMySessionSearchFinishedDelegate.Broadcast(true);
	}

	sessionInSearch = MakeShareable(new FOnlineSessionSearch);

	sessionInSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Near);

	sessionInSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";

	sessionInSearch->MaxSearchResults = 10;

	sessionInSearch->TimeoutInSeconds = 5;

	sessionInterface->FindSessions(0, sessionInSearch.ToSharedRef());
}

void UOurGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		auto result = sessionInSearch->SearchResults;
		for (int32 i = 0; i < result.Num(); i++) {
			if (result[i].IsValid() == false) {
				continue;
			}

			FSessionInfo info;
			info.Set(i, result[i]);

			FString roomName;
			result[i].Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
			FString hostName;
			result[i].Session.SessionSettings.Get(FName("HOST_NAME"), hostName);

			info.roomName = StringBase64Decode(roomName);
			info.hostName = StringBase64Decode(hostName);

			OnMySessionSearchCompleteDelegate.Broadcast(info);
		}
	}

	if (OnMySessionSearchFinishedDelegate.IsBound()) {
		OnMySessionSearchFinishedDelegate.Broadcast(false);
	}
}

void UOurGameInstance::JoinMySession(int32 index)
{
	sessionInterface->JoinSession(0, FName(*mySessionName), sessionInSearch->SearchResults[index]);
}

void UOurGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result)
{
	FTimerHandle tmer;
	GetWorld()->GetTimerManager().SetTimer(tmer, [&] {
		bisMulti = true;
		}, 1, false);	
	
	if (result == EOnJoinSessionCompleteResult::Success) {
		auto* pc = GetWorld()->GetFirstPlayerController();
		FString url;
		sessionInterface->GetResolvedConnectString(SessionName, url);

		if (!url.IsEmpty()) {
			pc->ClientTravel(url, ETravelType::TRAVEL_Absolute);
			
			// 클라이언트 트레블 할 때 로딩창 띄우기
			FTimerHandle timer;
			GetWorld()->GetTimerManager().SetTimer(timer, [&] {
				bdunloadStart = false;
				if (loadingEndDelegate.IsBound()) {
					loadingEndDelegate.Execute();
				}
				}, 7, false);
			
		}
	}
}

FString UOurGameInstance::StringBase64Encode(const FString& str)
{
	// Set 할 때 : FString -> UTF8 (std::string) -> TArray<uint8> -> base64 로 Encode
	std::string utf8String = TCHAR_TO_UTF8(*str);
	TArray<uint8> arrayData = TArray<uint8>((uint8*)(utf8String.c_str()), utf8String.length());
	return FBase64::Encode(arrayData);
}

FString UOurGameInstance::StringBase64Decode(const FString& str)
{
	// Get 할 때 : base64 로 Decode -> TArray<uint8> -> TCHAR
	TArray<uint8> arrayData;
	FBase64::Decode(str, arrayData);
	std::string ut8String((char*)(arrayData.GetData()), arrayData.Num());
	return UTF8_TO_TCHAR(ut8String.c_str());
}

