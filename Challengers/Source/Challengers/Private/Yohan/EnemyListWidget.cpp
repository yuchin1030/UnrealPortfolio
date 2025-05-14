// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/EnemyListWidget.h"
#include "OurGameInstance.h"
#include "Yohan/DungeonEditComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "ChallengersCharacter.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpectatorPawn.h>
#include "Yohan/DungeonEditCharacter.h"
#include "CHR/EnemySaveData.h"
#include "CHR/BaseEnemy.h"
#include "Yohan/DungeonEditWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanel.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


void UEnemyListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	button_enemySelect->OnClicked.AddDynamic(this, &UEnemyListWidget::EnemySelect);
	button_enemySelect->OnHovered.AddDynamic(this, &UEnemyListWidget::OnHovered);
	button_enemySelect->OnUnhovered.AddDynamic(this, &UEnemyListWidget::OnUnHovered);

	button_Remove->OnClicked.AddDynamic(this, &UEnemyListWidget::ClickRemove);

	Image_Select->SetOpacity(0);
	EW = Cast<UDungeonEditWidget>(GetParent()->GetOuter()->GetOuter());

}

void UEnemyListWidget::OnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UEnemyListWidget::OnUnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
}


void UEnemyListWidget::EnemySelect()
{
	// 컴포넌트가 가지고 있는 OnMouseClick 실행해야됨
	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;

	}
	if (dc)
	{
		auto* dEditComp = dc->FindComponentByClass<UDungeonEditComponent>();
		
		// 에너미를 마우스 커서 위치에 생성하는 함수. 인자는 에너미 세이브 데이터
		dEditComp->OnMouseClick(_bodyRowName, _weapon1RowName, _weapon2RowName, _gearRowName, _AIData);
	}
	
	if(EW!=nullptr)
	{ 
		EW->ChildInit1();
		Select1 = true;
	}
	else
	UE_LOG(LogTemp, Warning, TEXT("EW is Nullptr"));

}

void UEnemyListWidget::RemoveEnemy(FString __name)
{
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		gi->RemoveEnemy(__name);
	}

	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}
	// 삭제한 데이터가 보스가 아니라면
	if (_bIsBossType == false)
	{
		if (dc)
		{
			// 일반 몬스터 리스트 재로드
			dc->dungeonEditComponent->dungeonEditUI->ShowNormalEnemyList();			
		}
	}
	else
	{
		if (dc)
		{
			// 보스 몬스터 리스트 재로드
			dc->dungeonEditComponent->dungeonEditUI->ShowBossEnemyList();
		}
	}
	
}

void UEnemyListWidget::ClickRemove()
{
	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}
	dc->dungeonEditComponent->dungeonEditUI->name = _name;
	dc->dungeonEditComponent->dungeonEditUI->CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Visible);
	dc->dungeonEditComponent->dungeonEditUI->DeleteMonster->SetVisibility(ESlateVisibility::Visible);
	dc->dungeonEditComponent->dungeonEditUI->DeleteDungeon->SetVisibility(ESlateVisibility::Hidden);

}

void UEnemyListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(Select1 == true)
	{
		Image_Select->SetOpacity(0.3);
	}
	else
	{
		Image_Select->SetOpacity(0);
	}

}