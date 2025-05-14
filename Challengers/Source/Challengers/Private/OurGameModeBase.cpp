#include "OurGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "BJK/DungeonClearWidget.h"
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Yohan/EnemyCountInDungeonWidget.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LoadingWidget.h"
#include "Components/Image.h"
#include "BJK/CheckPointWidget.h"
#include "../../../../Source/Runtime/Engine/Public/EngineUtils.h"

AOurGameModeBase::AOurGameModeBase()
{
	// 틱이 돌도록 설정해야 된다.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void AOurGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOurGameModeBase, enemyTotal);
	DOREPLIFETIME(AOurGameModeBase, enemyCurrent);
	DOREPLIFETIME(AOurGameModeBase, clearTime);
	DOREPLIFETIME(AOurGameModeBase, bDungeonLoaded);
	DOREPLIFETIME(AOurGameModeBase, bDungoenLoadStart);
}

void AOurGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	auto cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (gi->bSLoading)
	{
		gi->bSLoading = false;

		// 싱글 플레이용 로딩 UI 띄우기
		if (sLoadingUI_BP)
		{
			sLoadingUI = CreateWidget<ULoadingWidget>(GetWorld(), sLoadingUI_BP);
			sLoadingUI->AddToViewport(1);
			sLoadingUI->HideAll();
		}
		if (GetWorld()->GetMapName().Contains(TEXT("Single")))
		{
			// 싱글 맵 로딩창 띄우기
			sLoadingUI->Image_Single->SetVisibility(ESlateVisibility::Visible);
		}
	}
	// 싱글 플레이 로딩창이 있다면 끄기
	if (sLoadingUI)
	{
		sLoadingUI->FadeOutStart(6);
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [&] {
			sLoadingUI->RemoveFromParent();
			if (ShowMapNameWidget_BP != nullptr)
			{
				ShowMapNameWidget = CreateWidget<UCheckPointWidget>(GetWorld(), ShowMapNameWidget_BP);
				if (ShowMapNameWidget)
				{
					ShowMapNameWidget->AddToViewport();

				}

			}
			if (loadingEndDelegate.IsBound()) {

				loadingEndDelegate.Execute();

			}

			}, 7, false);



	}

	// 던전 에디터용 코스트 연동
	if (cc)
	{
		gi->_enemyCost = cc->enemyCost;
	}
	/*for (TActorIterator<AMainPlayerController> it(GetWorld()); it; ++it)
	{
		auto playerCon = *it;
		playerCon->SetInputMode(FInputModeGameOnly());
	}*/
	
	
}

void AOurGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	bDungoenLoadStart = gi->bdunloadStart;

	// 던전 클리어 타이머 세팅
	// 던전이 로드가 되었다면..
	if (bDungeonLoaded)
	{
		if (bPlayerCount)
		{
			bPlayerCount = false;
						
			TArray<AActor*> ccArray;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), cc_BP, ccArray);

			playerCount = ccArray.Num();
			
			// 버프를 주기 위해 버프 매니저 생성
			BuffDebuffManagers = GetWorld()->SpawnActor<ABuffDebuffManager>(BuffDebuffManagerClass);
			BuffDebuffManagers->BuffDebuffStruct();
			UE_LOG(LogTemp, Warning, TEXT("Server Start"));
			
		}
		clearTime = FMath::Max(clearTime - DeltaSeconds, 0);

		if (clearTime <= 0)
		{
			// 타이머가 0이 된다면 bDungeonLoaded을 false로 한다
			bDungeonLoaded = false;

			bPlayerCount = true;
			cc->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		}
	}

	
}



