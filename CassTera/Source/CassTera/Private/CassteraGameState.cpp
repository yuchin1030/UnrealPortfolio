

#include "CassteraGameState.h"
#include "GameTimerWidget.h"
#include "ResultWidget.h"
#include "CassTeraCharacter.h"
#include "HidePlayer.h"
#include "HidePlayerCamera.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerState.h>
#include "HideAndSeekGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ACassteraGameState::ACassteraGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACassteraGameState::BeginPlay()
{
	Super::BeginPlay();

	resultWidget = Cast<UResultWidget>(CreateWidget(GetWorld(), wbp_resultWidget));

	timerWidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(), WBP_gameTimerWidget));
	timerWidget->AddToViewport();
	UE_LOG(LogTemp, Error, TEXT("start"));
}

void ACassteraGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (countDown <= 0)
	{
		//GetWorld()->GetTimerManager().ClearTimer(countHandle);
	}
}


void ACassteraGameState::ServerRPC_HidePlayerCount_Implementation()
{
	// 	hidePlayerCount = newHidePlayerCount;
	MultiRPC_HidePlayerCount(hidePlayerCount);
}

void ACassteraGameState::MultiRPC_HidePlayerCount_Implementation(int32 _hidePlayer)
{
	hidePlayerCount = _hidePlayer;
	if (timerWidget)
	{
		timerWidget->SetHidePlayerCount();
	}
}



void ACassteraGameState::ServerRPC_DecreaseHidePlayerCount_Implementation()
{
	hidePlayerCount -= 1;
	MultiRPC_DecreaseHidePlayerCount(hidePlayerCount);
	if (hidePlayerCount <= 0)
	{
		ServerRPC_CountDown();

	}
}

void ACassteraGameState::MultiRPC_DecreaseHidePlayerCount_Implementation(int32 _hidePlayer)
{
	hidePlayerCount = _hidePlayer;
	if (timerWidget)
	{
		timerWidget->SetHidePlayerCount();
		if (hidePlayerCount <= 0)
		{
			bCount = true;
			for (TActorIterator<AHidePlayerCamera> camera(GetWorld()); camera; ++camera)
			{
				hidePlayerCamera = *camera;
				if (hidePlayerCamera)
				{
					hidePlayerCamera->ServerRPC_Lose();

				}
			}
			for (TActorIterator<AHidePlayer> h(GetWorld()); h; ++h)
			{
				hidePlayer = *h;
				if (hidePlayer)
				{
					hidePlayer->ServerRPC_Lose();
				}
			}
			for (TActorIterator<ACassTeraCharacter> player(GetWorld()); player; ++player)
			{
				cassTeraPlayer = *player;
				if (cassTeraPlayer)
				{
					cassTeraPlayer->ServerRPC_Win();
				}
			}

		}
	}

}

void ACassteraGameState::ServerRPC_DecreaseTime_Implementation()
{
	bDecreasing = true;
	UE_LOG(LogTemp, Warning, TEXT("%d"), bDecreasing);

	if (!(minute == 0 && seconds <= 30))
	{
		pgPercent += (1.0f / totalSeconds * minusSeconds);

	}

	if (minute > 0 && seconds < 10)
	{
		minute -= 1;
		seconds += 51;
	}
	else if (minute == 0 && seconds < 10)
	{
		seconds = 0;
	}
	else if (!(minute == 0 && seconds <= 30))	// ����Ÿ�� �����ϰ�� ��� 10�ʾ� ����
	{
		seconds -= minusSeconds;
	}



	MultiRPC_DecreaseTime(bDecreasing, minute, seconds, minusSeconds, pgPercent, totalSeconds);
}

void ACassteraGameState::MultiRPC_DecreaseTime_Implementation(bool _bDecreasing, int32 _minute, int32 _seconds, int32 _minusSeconds, float _pgPercent, float _totalSeconds)
{
	bDecreasing = _bDecreasing;
	minute = _minute;
	seconds = _seconds;
	minusSeconds = _minusSeconds;
	pgPercent = _pgPercent;
	totalSeconds = _totalSeconds;

	timerWidget->Timer();

	bDecreasing = false;
	UE_LOG(LogTemp, Warning, TEXT("%d"), bDecreasing);

}

void ACassteraGameState::ServerRPC_CountDown_Implementation()
{
	//auto pc = GetNetOwningPlayer()->PlayerController;
	auto* pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	

	countDown = 10;
	FTimerHandle goHandle;
	if (pc->IsLocalController())
	{
		GetWorld()->GetTimerManager().SetTimer(goHandle, [&]() {
			//�ڲ������� �ּ�ó��
			bCount = true;
			GetWorld()->GetTimerManager().ClearTimer(countHandle);
			GetWorld()->GetTimerManager().ClearTimer(timerHandler);
			GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/WaitngMap?listen"));
			
			// ���Ŀ� �ٽ� ���Ƿ� ���ư��� ���� ���� �ν��Ͻ��� ���� ����(���� ������Ʈ�� �޶� ��� ������ ���� ������Ʈ�� ������. �׷��� �������� �ν��Ͻ����� �����ؾ���
			bIsTraveld = true;
			}, 10.f, false);
	}
	/*FTimerHandle startGame;
	GetWorld()->GetTimerManager().SetTimer(startGame, [&]() {
		GetWorld()->ServerTravel(TEXT("/Game/Yohan/Maps/SchoolMap?listen"));
			}, 30, false);
	*/

	GetWorld()->GetTimerManager().SetTimer(countHandle, [&]() {
		countDown -= 1;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ī��Ʈ�ٿ� ������ serverTravel �ϸ� ���⼭ ����, �� Ÿ�̸��ڵ��� ������� �ϴµ� �� 
		MultiRPC_CountDown(countDown);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}, 1.0f, true);

}

void ACassteraGameState::MultiRPC_CountDown_Implementation(int32 _Count)
{
	countDown = _Count;
	if (resultWidget)
	{
		resultWidget->SetTimer();
	}
	// 	bCount = false;
}

void ACassteraGameState::ServerRPC_CalculateTime_Implementation()
{
	if (bClearTimer == false)
	{
		bClearTimer = true;

		GetWorld()->GetTimerManager().SetTimer(timerHandler, [&]() {
			//UE_LOG(LogTemp, Warning, TEXT("%d, %d"), minute, seconds);

			// ���α׷����� Ÿ�̸�
			pgPercent += (1.0f / totalSeconds);
			// pg_Timer->SetPercent(pgPercent);

			// ���� Ÿ�̸�
			if (minute >= 0 && seconds > 0)
			{
				seconds -= 1;
				UE_LOG(LogTemp, Warning, TEXT("time -1"));

			}
			else if (minute > 0 && seconds == 0)
			{
				minute -= 1;
				seconds = 59;
				UE_LOG(LogTemp, Warning, TEXT("time 59"));
			}

			MultiRPC_CalculateTime(bClearTimer, minute, seconds, pgPercent, totalSeconds);
		}, 1.0f, true);
	}
}

void ACassteraGameState::MultiRPC_CalculateTime_Implementation(bool _bClearTimer, int32 _minute, int32 _seconds, float _pgPercent, float _totalSeconds)
{
	bClearTimer = _bClearTimer;
	minute = _minute;
	seconds = _seconds;
	pgPercent = _pgPercent;
	totalSeconds = _totalSeconds;

	if (timerWidget) {

		timerWidget->Timer();
		//UE_LOG(LogTemp, Warning, TEXT("timer"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("timerNone"));
	}

	bClearTimer = false;
}
void ACassteraGameState::ServerRPC_ShowResult_Implementation()
{
	bCount = true;
	MultiRPC_ShowResult();
}

void ACassteraGameState::MultiRPC_ShowResult_Implementation()
{
	bCount = true;
	for (TActorIterator<AHidePlayerCamera> camera(GetWorld()); camera; ++camera)
	{
		hidePlayerCamera = *camera;
		if (hidePlayerCamera)
		{
			hidePlayerCamera->ServerRPC_Win();

		}
	}
	for (TActorIterator<AHidePlayer> h(GetWorld()); h; ++h)
	{
		hidePlayer = *h;
		if (hidePlayer)
		{
			hidePlayer->ServerRPC_Win();
		}
	}
	for (TActorIterator<ACassTeraCharacter> player(GetWorld()); player; ++player)
	{
		cassTeraPlayer = *player;
		if (cassTeraPlayer)
		{
			cassTeraPlayer->ServerRPC_Lose();
		}
	}
}
void ACassteraGameState::ServerRPC_ShowResult2_Implementation()
{
	bCount = true;
	MultiRPC_ShowResult2();
	ServerRPC_CountDown();
}

void ACassteraGameState::MultiRPC_ShowResult2_Implementation()
{
	bCount = true;
	for (TObjectPtr<APlayerState> ps : PlayerArray)
	{
		auto* pawn = ps->GetPawn();
		if (pawn->IsA<AHidePlayerCamera>())
		{
			Cast<AHidePlayerCamera>(pawn)->ServerRPC_Lose();
		}
		else if (pawn->IsA<ACassTeraCharacter>())
		{
			Cast<ACassTeraCharacter>(pawn)->ServerRPC_Win();
		}
	}

}
