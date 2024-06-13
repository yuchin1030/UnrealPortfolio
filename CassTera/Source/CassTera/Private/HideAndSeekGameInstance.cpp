	// Fill out your copyright notice in the Description page of Project Settings.


#include "HideAndSeekGameInstance.h"
#include <OnlineSubsystem.h>
#include <Interfaces/OnlineSessionInterface.h>
#include <Online/OnlineSessionNames.h>
#include "CassteraGameState.h"
#include <../../../../../../../Source/Runtime/Core/Public/Containers/Ticker.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>



void UHideAndSeekGameInstance::Init()
{
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UHideAndSeekGameInstance::Tick));

	Super::Init();

	

	// ����ý��ۿ��� ���� �������̽� ��������
	auto subsys = IOnlineSubsystem::Get();
	if (subsys)
	{
		sessionInterface = subsys->GetSessionInterface();

		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UHideAndSeekGameInstance::OnCreateSessionCompleted);

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UHideAndSeekGameInstance::OnFindSessionsComplete);

		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UHideAndSeekGameInstance::OnJoinSessionComplete);
	}

	/*FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, [&]() {
		CreateMySession(TEXT("School"), 3);
		}, 3.0f, false);*/
}




void UHideAndSeekGameInstance::CreateMySession(FString roomName, int32 playerCount)
{
	FOnlineSessionSettings set;

	// 1. ��������Ʈ ���� �����ΰ�? false
	set.bIsDedicated = false;

	// 2. �������� ��Ī�� ���ΰ�? subsys �̸��� �ٸ��� false
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	set.bIsLANMatch = subsysName == "NULL";

	// 3. ��Ī�� ������ ���ΰ�?( <-> ģ�� �ʴ�θ� �� ���ΰ�?)
	set.bShouldAdvertise = true;

	// 4. Presesce�� ����� ���ΰ�?
	set.bUsesPresence = true;

	// 5. ���� ���߿� �������� ����
	set.bAllowJoinInProgress = true;
	set.bAllowJoinViaPresence = true;

	// 6. ������ ���� ������ �ִ� ����
	set.NumPublicConnections = playerCount;

	// 7. Ŀ���� ���� : �� �̸�, ȣ��Ʈ �̸�
	set.Set(FName("ROOM_NAME"), StringBase64Encode(roomName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	set.Set(FName("HOST_NAME"), StringBase64Encode(mySessionName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// 8. netID�� ���� ���� �ʹ�
	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();
	
	UE_LOG(LogTemp, Warning, TEXT("CreateMySession : %s"), *roomName);

	// �������̽��� �� ����� ��û
	sessionInterface->CreateSession(*netID,FName(*roomName), set);
}

void UHideAndSeekGameInstance::OnCreateSessionCompleted(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete -> sessionName : %s, bwasSuccessful : %d"), *sessionName.ToString(), bWasSuccessful);
		 
	// ����� ������ �ߴٸ�, �������� ServerTravel�ϰ� �ʹ�
	if (bWasSuccessful)
	{
		GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/WaitngMap?listen"));

		// ��� �� ���� �� 30�� �ڿ� ���� ������ ServerTravel�ϰ� �ʹ�
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [&]() {
			GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/SchoolMap?listen"));
			UE_LOG(LogTemp, Error, TEXT("SchoolMap Open"));
			}, 30, false);

		
	}
}

bool UHideAndSeekGameInstance::IsInRoom()
{
	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	return sessionInterface->IsPlayerInSession(FName(*mySessionName), *netID);
}

void UHideAndSeekGameInstance::FindOtherSessions()
{
	if (OnMySessionSearchFinishedDelegate.IsBound())
	{
		OnMySessionSearchFinishedDelegate.Broadcast(true);
	}

	// ���� �������̽��� �̿��ؼ� ���� ã�� �ʹ�
	sessionInSearch = MakeShareable(new FOnlineSessionSearch);
	
	// �˻� ������ �����ϰ� �ʹ�
	sessionInSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	// LAN ����
	sessionInSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";

	// �ִ�� �˻��� �� �ִ� ���� ����
	sessionInSearch->MaxSearchResults = 10;

	sessionInterface->FindSessions(0, sessionInSearch.ToSharedRef());
}

void UHideAndSeekGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	// �� ã�⿡ �����ߴٸ�
	if (bWasSuccessful)
	{
		// sessionInSearch���� ������ �������� �ʹ�. -> UI�� ǥ���ϰ� �ʹ�
		auto results = sessionInSearch->SearchResults;
		if (results.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete results.Num() == 0"));
		}
		for (int i = 0; i < results.Num(); i++)
		{
			auto item = results[i];
			if (false == item.IsValid())
			{
				continue;
			}
			
			FSessionInfo info;
			info.Set(i, item);

			FString roomName;
			FString hostName;
			item.Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
			item.Session.SessionSettings.Get(FName("HOST_NAME"), hostName);

			info.roomName = StringBase64Decode(roomName);
			info.hostName = StringBase64Decode(hostName);

			OnMySessionSearchCompleteDelegate.Broadcast(info);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *info.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete bWasSuccessful is false"));
		OnMySessionSearchFinishedDelegate.Broadcast(false);
	}
}

void UHideAndSeekGameInstance::JoinMySession(int32 index)
{
	sessionInterface->JoinSession(0, FName(*mySessionName), sessionInSearch->SearchResults[index]);
}

void UHideAndSeekGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result)
{
	// ȣ��Ʈ�� IP, Port��ȣ�� �����ͼ� ClientTravel �ϰ�ʹ�.
	if (result == EOnJoinSessionCompleteResult::Success)
	{
		auto* pc = GetWorld()->GetFirstPlayerController();
		FString url;
		sessionInterface->GetResolvedConnectString(SessionName, url);
		UE_LOG(LogTemp, Warning, TEXT("ClientTravel URL : %s"), *url);

		if (false == url.IsEmpty())
		{
			pc->ClientTravel(url, ETravelType::TRAVEL_Absolute);
		}
	}
}

FString UHideAndSeekGameInstance::StringBase64Encode(const FString& str)
{
	// Set �� �� : FString -> UTF8 (std::string) -> TArray<uint8> -> base64 �� Encode
	std::string utf8String = TCHAR_TO_UTF8(*str);
	TArray<uint8> arrayData = TArray<uint8>((uint8*)(utf8String.c_str()), utf8String.length());
	return FBase64::Encode(arrayData);
}

FString UHideAndSeekGameInstance::StringBase64Decode(const FString& str)
{
	// Get �� �� : base64 �� Decode -> TArray<uint8> -> TCHAR
	TArray<uint8> arrayData;
	FBase64::Decode(str, arrayData);
	std::string ut8String((char*)(arrayData.GetData()), arrayData.Num());
	return UTF8_TO_TCHAR(ut8String.c_str());
}

bool UHideAndSeekGameInstance::Tick(float DeltaSeconds)
{
	cgs = Cast<ACassteraGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (cgs)
	{
		// ���� ������Ʈ���� �������� ���� Ʈ������ �ߴٸ�
		if (cgs->bIsTraveld == true)
		{
			cgs->bIsTraveld = false;
			FTimerHandle startGame;
			GetWorld()->GetTimerManager().SetTimer(startGame, [&]() {
				GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/SchoolMap?listen"));
				}, 30, false);
		}
	}
	//FDelegateHandle TickDelegateHandle;
	//auto* pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	//cgs = Cast<ACassteraGameState>(UGameplayStatics::GetGameState(GetWorld()));
	//if (cgs) 
	//{
	//	if (cgs->countDown <= 0)
	//	{
	//		cgs->countDown = 10;
	//		FTimerHandle goHandle;
	//		if (pc->IsLocalController())
	//		{
	//			GetWorld()->GetTimerManager().SetTimer(goHandle, [&]() {
	//				//�ڲ������� �ּ�ó��
	//				cgs->bCount = true;
	//				GetWorld()->GetTimerManager().ClearTimer(cgs->countHandle);
	//				GetWorld()->GetTimerManager().ClearTimer(cgs->timerHandler);
	//				GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/WaitngMap?listen"));

	//				}, 10.f, false);
	//		}
	//		FTimerHandle startGame;
	//		GetWorld()->GetTimerManager().SetTimer(startGame, [&]() {
	//			GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/SchoolMap?listen"));
	//			}, 30, false);
	//	}
	//}
	
	return true;
}


void UHideAndSeekGameInstance::Shutdown()
{
	// Unregister ticker delegate
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	Super::Shutdown();
}
