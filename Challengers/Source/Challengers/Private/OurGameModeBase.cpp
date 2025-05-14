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
	// ƽ�� ������ �����ؾ� �ȴ�.
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

		// �̱� �÷��̿� �ε� UI ����
		if (sLoadingUI_BP)
		{
			sLoadingUI = CreateWidget<ULoadingWidget>(GetWorld(), sLoadingUI_BP);
			sLoadingUI->AddToViewport(1);
			sLoadingUI->HideAll();
		}
		if (GetWorld()->GetMapName().Contains(TEXT("Single")))
		{
			// �̱� �� �ε�â ����
			sLoadingUI->Image_Single->SetVisibility(ESlateVisibility::Visible);
		}
	}
	// �̱� �÷��� �ε�â�� �ִٸ� ����
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

	// ���� �����Ϳ� �ڽ�Ʈ ����
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

	// ���� Ŭ���� Ÿ�̸� ����
	// ������ �ε尡 �Ǿ��ٸ�..
	if (bDungeonLoaded)
	{
		if (bPlayerCount)
		{
			bPlayerCount = false;
						
			TArray<AActor*> ccArray;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), cc_BP, ccArray);

			playerCount = ccArray.Num();
			
			// ������ �ֱ� ���� ���� �Ŵ��� ����
			BuffDebuffManagers = GetWorld()->SpawnActor<ABuffDebuffManager>(BuffDebuffManagerClass);
			BuffDebuffManagers->BuffDebuffStruct();
			UE_LOG(LogTemp, Warning, TEXT("Server Start"));
			
		}
		clearTime = FMath::Max(clearTime - DeltaSeconds, 0);

		if (clearTime <= 0)
		{
			// Ÿ�̸Ӱ� 0�� �ȴٸ� bDungeonLoaded�� false�� �Ѵ�
			bDungeonLoaded = false;

			bPlayerCount = true;
			cc->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		}
	}

	
}



