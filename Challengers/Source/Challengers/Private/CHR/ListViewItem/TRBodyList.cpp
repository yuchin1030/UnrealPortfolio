// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/ListViewItem/TRBodyList.h"
#include "CHR/TestRoomGameMode.h"
#include "CHR/TestRoomSetWidget.h"
#include "GJY/Weapon1Object.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListViewBase.h"
#include "EngineUtils.h"
#include "SkillStruct.h"

void UTRBodyList::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	WO = Cast<UWeapon1Object>(ListItemObject);

	SelectButton->OnClicked.RemoveDynamic(this, &UTRBodyList::ClickSelectButton);
	SelectButton->OnClicked.AddDynamic(this, &UTRBodyList::ClickSelectButton);

	HPText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.HP)));
	WeightText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.weightLimit)));
	CostText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.cost)));
	NameText->SetText(FText::FromString(WO->BodyObject.name));

	if (WO->bIsEquiped)
	{
		TextBlock_true->SetVisibility(ESlateVisibility::Visible);
	}
	else{
		TextBlock_true->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WO->BodyObject.bIsBossType)
	{
		Image_Type_Boss->SetVisibility(ESlateVisibility::Visible);
		Image_Type_Mon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Image_Type_Boss->SetVisibility(ESlateVisibility::Hidden);
		Image_Type_Mon->SetVisibility(ESlateVisibility::Visible);
	}

	Body = WO->_RowName;
	indexNum = WO->indexNum;
}

void UTRBodyList::ClickSelectButton()
{
	UTestRoomSetWidget* TRSW = Cast<UTestRoomSetWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (TRSW)
	{
		TRSW->bodyRowName = Body;
		TRSW->ResetEuqipState(0, indexNum);
	}

	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (TRGM->enemyREF)
	{
		TRGM->enemyREF->ChangeBody(Body);
		TRGM->enemyREF->CheakWeightLimit();
	}

	if (TRSW)
	{
		//금액갱신
		TRSW->UpdateMonsterCost();
		TRSW->SetEnemySpec(0, Body);
	}

}
