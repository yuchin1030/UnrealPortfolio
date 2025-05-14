// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/OurGameStateBase.h"
#include "OurGameModeBase.h"
#include "Yohan/EnemyCountInDungeonWidget.h"
#include "LoadingWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Public/Net/UnrealNetwork.h>
#include "MainPlayerController.h"
#include "../BJK/DungeonClearFailWidget.h"
#include "OurGameInstance.h"
#include "Components/Image.h"
#include "../../../EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "BJK/CheckPointWidget.h"
#include "EngineUtils.h"

AOurGameStateBase::AOurGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
}

void AOurGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());

	pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// 로딩 창 띄우는 중
	if (HasAuthority())
	{
		if (gm)
		{
			// 게임 모드의 던전 로드가 시작됐음을 알리는 변수를 받아온다
			_bisDunLoadStart = gm->bDungoenLoadStart;
		}
	}
	// 로딩 UI를 만들어놓고 숨긴다
	loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);
	loadingUI->AddToViewport(1);
	loadingUI->HideAll();
	
	// 던전 타이머/에너미 카운터 띄우기
	if (enemyCountUI_BP)
	{
		enemyCountUI = CreateWidget<UEnemyCountInDungeonWidget>(GetWorld(), enemyCountUI_BP);
		enemyCountUI->AddToViewport();
		enemyCountUI->SetVisibility(ESlateVisibility::Hidden);
	}

	pc->SetInputMode(FInputModeGameOnly());
	cc->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	ClearWidget_Cost = gi->createDunCost;
}

void AOurGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (HasAuthority())
	{
		// 서버가 게임모드의 값들을 넘겨 받는다.
		if (gm)
		{
			bisDunLoad = gm->bDungeonLoaded;
			_cleatTimer = gm->clearTime;
			_enemyTotal = gm->enemyTotal;
			_enemyCurrent = gm->enemyCurrent;
			_bDungeonFinished = gm->bDungeonFinished;
			_playerCount = gm->playerCount;
			_bisDunLoadStart = gm->bDungoenLoadStart;
		}
		if (gi)
		{
			bisMulti = gi->bisMulti;
			bisDun = gi->bisDun;
			_bisSteam = gi->bisSteam;
			_bisCyber = gi->bisCyber;
		}
	}	
	// 던전 로드가 시작됐을 때
	if (_bisDunLoadStart)
	{
		if (bisMulti)
		{
			// 로딩 UI를 보이게 한다		
			loadingUI->Image_Multi->SetVisibility(ESlateVisibility::Visible);			
		}
		else if (_bisSteam)
		{
			// 스팀펑크 던전 UI
			loadingUI->Image_Steam->SetVisibility(ESlateVisibility::Visible);
		}
		else if (bisDun)
		{		
			// 디젤 펑크 던전 UI
			loadingUI->Image_Dissel->SetVisibility(ESlateVisibility::Visible);		
		}		
		else if (_bisCyber)
		{
			// 사이버 펑크 던전 UI
			loadingUI->Image_Cyber->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (!_bisDunLoadStart && !bIsLoadingEndCheak1)
	{
		// 던전 로드가 완료 됐을 때, 로딩 UI를 숨긴다
		loadingUI->FadeOutStart(0);
		FTimerHandle fadeTimer;
		GetWorld()->GetTimerManager().SetTimer(fadeTimer, [&] {
			if (loadingUI)
			{
				loadingUI->SetVisibility(ESlateVisibility::Hidden);
			}
			}, 1, false);
		
		if (HasAuthority())
		{
			gi->bisMulti = false;
			gi->bisDun = false;
			gi->bisSteam = false;
			if (_bisCyber == true)
			{
				FTimerHandle t;
				GetWorld()->GetTimerManager().SetTimer(t, [&]{ gi->bisCyber = false; }, 4, false);
			}		
			
			if (!Test)
			{
				if (ShowMapNameWidget_BP != nullptr)
				{
					ShowMapNameWidget = CreateWidget<UCheckPointWidget>(GetWorld(), ShowMapNameWidget_BP);
					if (ShowMapNameWidget)
					{
						ShowMapNameWidget->AddToViewport();
						Test =true;

					}

				}
			}
			

			if (loadingEndDelegate.IsBound()) {
				loadingEndDelegate.Execute();
			}
		}
		bIsLoadingEndCheak1 = true;
	}

	if (bisDunLoad && _playerCount <= 0 && !bisFailedUI)
	{
		// 플레이어가 전멸했다면, 실패 UI 띄운다
		ClearFailed();

		bisFailedUI = true;
	}

	if (_cleatTimer <= 0  && !bisFailedUI)
	{
		// 타이머가 다 돌았고, 에너미가 남았을 때 실패 UI 뜸
		if (_enemyCurrent >= 1)
		{
			ClearFailed();
		}
	

		bisFailedUI = true;
	}

	if (true == bisDunLoad && !bIsLoadingEndCheak2)
	{
		if (HasAuthority())
		{
			
			gi->bdunloadStart = false;
		}	
		// 던전 로드가 완료 됐을 때, 로딩 UI를 숨긴다
		loadingUI->FadeOutStart(0);
		FTimerHandle fadeTimer;
		GetWorld()->GetTimerManager().SetTimer(fadeTimer, [&] {
			if (loadingUI)
			{
				loadingUI->SetVisibility(ESlateVisibility::Hidden);
			}
			}, 1, false);

		// 던전이 로드가 되었다면, 에너미 카운트 UI를 보이게 한다
		enemyCountUI->SetVisibility(ESlateVisibility::Visible);
		
		
		bisFailedUI = false;
		bIsLoadingEndCheak2 = true;
	}

	if (true == _bDungeonFinished)
	{		
		ISDungeonFinished();
		
		if (HasAuthority())
		{
			gm->bDungeonFinished = false;
		}
	}
}

void AOurGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOurGameStateBase, bisDunLoad);
	DOREPLIFETIME(AOurGameStateBase, _cleatTimer);
	DOREPLIFETIME(AOurGameStateBase, _enemyTotal);
	DOREPLIFETIME(AOurGameStateBase, _enemyCurrent);
	DOREPLIFETIME(AOurGameStateBase, _bDungeonFinished);
	DOREPLIFETIME(AOurGameStateBase, _playerCount);
	DOREPLIFETIME(AOurGameStateBase, _bisDunLoadStart);
	DOREPLIFETIME(AOurGameStateBase, bisMulti);
	DOREPLIFETIME(AOurGameStateBase, bisDun);
	DOREPLIFETIME(AOurGameStateBase, _bisSteam);
	DOREPLIFETIME(AOurGameStateBase, _bisCyber);
	DOREPLIFETIME(AOurGameStateBase, ClearWidget_Cost);
}

void AOurGameStateBase::ISDungeonFinished()
{
	// 던전이 끝났다면
	if (HasAuthority())
	{
		gm->bDungeonLoaded = false;	
	}

	FTimerHandle timer;

	// 3초 뒤에 던전 클리어 UI 뜨게 한다
	GetWorld()->GetTimerManager().SetTimer(timer, [&] {
		
		ServerRPC_EXP();

	}, 3, false);		

}

void AOurGameStateBase::ServerRPC_EXP_Implementation()
{
	MultiRPC_EXP();
}

void AOurGameStateBase::MultiRPC_EXP_Implementation()
{
	if (pc)
	{
		pc->CreateDungeonClearWidget();
		cc->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

		for (TActorIterator<AChallengersCharacter> it(GetWorld()); it; ++it)
		{

			AChallengersCharacter* player = *it;
			player->SetPlayerExpAndLevel();

			UE_LOG(LogTemp, Warning, TEXT("SetPlayerExpAndLevel"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("pc"));
	}
}


void AOurGameStateBase::ClearFailed()
{
	if (dungeonClearFail_BP)
	{
		dungeonClearFailUI = CreateWidget<UDungeonClearFailWidget>(GetWorld(), dungeonClearFail_BP);

		dungeonClearFailUI->AddToViewport();
		cc->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	
}

