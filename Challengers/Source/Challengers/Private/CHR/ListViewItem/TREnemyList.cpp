// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/ListViewItem/TREnemyList.h"
#include "CHR/TestRoomLoadWidget.h"
#include "CHR/TestRoomGameMode.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "EngineUtils.h"
#include "OurGameInstance.h"

void UTREnemyList::NativeConstruct()
{
	Super::NativeConstruct();

	button_enemySelect->OnClicked.AddDynamic(this, &UTREnemyList::EnemySelect);
	button_enemySelect->OnHovered.AddDynamic(this, &UTREnemyList::OnHovered);
	button_enemySelect->OnUnhovered.AddDynamic(this, &UTREnemyList::OnUnHovered);

	button_Remove->OnClicked.AddDynamic(this, &UTREnemyList::ClickRemove);
}

void UTREnemyList::OnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UTREnemyList::OnUnHovered()
{
	UUserWidget::PlayAnimation(SelectAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
}


void UTREnemyList::EnemySelect()
{
	//�����͸� �ε��ؼ� ���ʹ̿� �����Ѵ�
	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());

	if (TRGM) {
		TRGM->bodyRowName = _bodyRowName;
		TRGM->weapon1RowName = _weapon1RowName;
		TRGM->weapon2RowName = _weapon2RowName;
		TRGM->gearRowName = _gearRowName;
		TRGM->AIData = _AIData;

		TRGM->SpawnEnemy();

		if (TRGM->enemyREF) {
			TRGM->enemyREF->enemySpec.name = _name;
		}
		TRGM->currentEnemyName = _name;
	}
}

void UTREnemyList::RemoveEnemy(FString __name)
{
	auto* gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		gi->RemoveEnemy(__name);
	}
	//Ȯ���ʿ�
	UTestRoomLoadWidget* TRLW = Cast<UTestRoomLoadWidget>(GetParent()->GetOuter()->GetOuter());

	// ������ �����Ͱ� ������ �ƴ϶��
	if (_bIsBossType == false)
	{
		if (TRLW)
		{
			// �Ϲ� ���� ����Ʈ ��ε�
			TRLW->ShowNormalEnemyList();
		}
	}
	else
	{
		if (TRLW)
		{
			// ���� ���� ����Ʈ ��ε�
			TRLW->ShowBossEnemyList();
		}
	}

}

void UTREnemyList::ClickRemove()
{
	//Ȯ���ʿ�
	UTestRoomLoadWidget* TRLW = Cast<UTestRoomLoadWidget>(GetParent()->GetOuter()->GetOuter());
	if (TRLW)
	{
		TRLW->name = _name;
		TRLW->CanvasPannel_RemoveQuestion->SetVisibility(ESlateVisibility::Visible);
		//TRLW->DeleteMonster->SetVisibility(ESlateVisibility::Visible);
	}
}
