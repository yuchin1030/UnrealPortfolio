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

	// �ε� â ���� ��
	if (HasAuthority())
	{
		if (gm)
		{
			// ���� ����� ���� �ε尡 ���۵����� �˸��� ������ �޾ƿ´�
			_bisDunLoadStart = gm->bDungoenLoadStart;
		}
	}
	// �ε� UI�� �������� �����
	loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);
	loadingUI->AddToViewport(1);
	loadingUI->HideAll();
	
	// ���� Ÿ�̸�/���ʹ� ī���� ����
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
		// ������ ���Ӹ���� ������ �Ѱ� �޴´�.
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
	// ���� �ε尡 ���۵��� ��
	if (_bisDunLoadStart)
	{
		if (bisMulti)
		{
			// �ε� UI�� ���̰� �Ѵ�		
			loadingUI->Image_Multi->SetVisibility(ESlateVisibility::Visible);			
		}
		else if (_bisSteam)
		{
			// ������ũ ���� UI
			loadingUI->Image_Steam->SetVisibility(ESlateVisibility::Visible);
		}
		else if (bisDun)
		{		
			// ���� ��ũ ���� UI
			loadingUI->Image_Dissel->SetVisibility(ESlateVisibility::Visible);		
		}		
		else if (_bisCyber)
		{
			// ���̹� ��ũ ���� UI
			loadingUI->Image_Cyber->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (!_bisDunLoadStart && !bIsLoadingEndCheak1)
	{
		// ���� �ε尡 �Ϸ� ���� ��, �ε� UI�� �����
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
		// �÷��̾ �����ߴٸ�, ���� UI ����
		ClearFailed();

		bisFailedUI = true;
	}

	if (_cleatTimer <= 0  && !bisFailedUI)
	{
		// Ÿ�̸Ӱ� �� ���Ұ�, ���ʹ̰� ������ �� ���� UI ��
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
		// ���� �ε尡 �Ϸ� ���� ��, �ε� UI�� �����
		loadingUI->FadeOutStart(0);
		FTimerHandle fadeTimer;
		GetWorld()->GetTimerManager().SetTimer(fadeTimer, [&] {
			if (loadingUI)
			{
				loadingUI->SetVisibility(ESlateVisibility::Hidden);
			}
			}, 1, false);

		// ������ �ε尡 �Ǿ��ٸ�, ���ʹ� ī��Ʈ UI�� ���̰� �Ѵ�
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
	// ������ �����ٸ�
	if (HasAuthority())
	{
		gm->bDungeonLoaded = false;	
	}

	FTimerHandle timer;

	// 3�� �ڿ� ���� Ŭ���� UI �߰� �Ѵ�
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

