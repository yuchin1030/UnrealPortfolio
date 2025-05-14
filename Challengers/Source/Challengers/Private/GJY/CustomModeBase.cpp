#include "GJY/CustomModeBase.h"
#include "GJY/PlayerCustomizer.h"
#include "GJY/EnemyCustomizer.h"
#include "GJY/AISettingCustomizer.h"
#include "CHR/BaseEnemy.h"
#include "LoadingWidget.h"
#include "Components/Image.h"

ACustomModeBase::ACustomModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	FString CurrentLevelName = GetWorld()->GetMapName();

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	if (CurrentLevelName.Contains(TEXT("Char")))
	{ 
		ShowCharacterCustomizer();
		// 로딩 UI Add to ViewPort 하셈
		if (loadingUI_BP)
		{
			// 로딩 UI 띄우기
			loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);

			loadingUI->AddToViewport(1);

			// 캐릭터 커스터마이저 용 로딩창만 띄우기
			loadingUI->HideAll();
			loadingUI->Image_Char->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		ShowEnemyCustomizer();
		// 로딩 UI Add to ViewPort 하셈
		if (loadingUI_BP)
		{
			// 로딩 UI 띄우기
			loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);

			loadingUI->AddToViewport(1);

			// 에너미 커스터마이저 용 로딩창만 띄우기
			loadingUI->HideAll();
			loadingUI->Image_Single->SetVisibility(ESlateVisibility::Visible);
		}
	}

	// 로딩 UI Remove From Parent 하셈, 타이머 걸어서 하면 편함.
	loadingUI->FadeOutStart(4);
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, [&] {
		if (loadingUI)
		{
			loadingUI->RemoveFromParent();
			if (loadingEndDelegate.IsBound()) {
				loadingEndDelegate.Execute();
			}
		}
	}, 5, false);
}

void ACustomModeBase::Tick(float DeltaTime)
{
	if (bIsRotate && CustomEnemy) {
		if (bIsBack) {
			CustomEnemy->SetActorRotation(FRotator(0.0f, FMath::InterpEaseOut(180.0f, 0.0f, GetWorld()->GetTimerManager().GetTimerElapsed(rotateTimer)/0.5f, 2.0f), 0.0f));
		}
		else {
			CustomEnemy->SetActorRotation(FRotator(0.0f, FMath::InterpEaseOut(0.0f, 180.0f, GetWorld()->GetTimerManager().GetTimerElapsed(rotateTimer) / 0.5f, 2.0f), 0.0f));
		}
	}
}

void ACustomModeBase::ShowCharacterCustomizer()
{
	if (CustomWidget != nullptr)
	{
		Custom_Inst = CreateWidget<UPlayerCustomizer>(GetWorld(), CustomWidget);

		if (Custom_Inst)
		{
			Custom_Inst->AddToViewport(0);
		}
	}
}

void ACustomModeBase::ShowEnemyCustomizer()
{
	if (EnemyWidget != nullptr)
	{
		Enemy_Inst = CreateWidget<UEnemyCustomizer>(GetWorld(), EnemyWidget);

		if (Enemy_Inst)
		{
			Enemy_Inst->AddToViewport(0);
		}

	}
}

void ACustomModeBase::ShowAISettingUI()
{
	if(AIWidget != nullptr)
	{
		AI_Inst = CreateWidget<UAISettingCustomizer>(GetWorld(),AIWidget);

		if(AI_Inst)
		{
			AI_Inst->AddToViewport();
			Enemy_Inst->SetVisibility(ESlateVisibility::Hidden);
		}
	
	}
}

void ACustomModeBase::RotateEnemy(ABaseEnemy* RotateEnemy, bool _bIsBack)
{
	CustomEnemy = RotateEnemy;
	bIsRotate = true;
	bIsBack = _bIsBack;
	if (_bIsBack) {
		GetWorld()->GetTimerManager().SetTimer(rotateTimer, FTimerDelegate::CreateLambda([&]() {
			CustomEnemy->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
			bIsRotate = false;
			}), 0.5f, false);
	}
	else {
		GetWorld()->GetTimerManager().SetTimer(rotateTimer, FTimerDelegate::CreateLambda([&]() {
			CustomEnemy->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
			bIsRotate = false;
			}), 0.5f, false);
	}
}
