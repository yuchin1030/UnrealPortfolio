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
	// ������Ʈ�� ������ �ִ� OnMouseClick �����ؾߵ�
	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;

	}
	if (dc)
	{
		auto* dEditComp = dc->FindComponentByClass<UDungeonEditComponent>();
		
		// ���ʹ̸� ���콺 Ŀ�� ��ġ�� �����ϴ� �Լ�. ���ڴ� ���ʹ� ���̺� ������
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
	// ������ �����Ͱ� ������ �ƴ϶��
	if (_bIsBossType == false)
	{
		if (dc)
		{
			// �Ϲ� ���� ����Ʈ ��ε�
			dc->dungeonEditComponent->dungeonEditUI->ShowNormalEnemyList();			
		}
	}
	else
	{
		if (dc)
		{
			// ���� ���� ����Ʈ ��ε�
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