// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/ListViewItem/TRAbilityList.h"
#include "CHR/TestRoomGameMode.h"
#include "CHR/TestRoomSetWidget.h"
#include "CHR/BaseEnemy.h"
#include "EngineUtils.h"
#include "OurGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ListViewBase.h"
#include "GJY/Weapon1Object.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UTRAbilityList::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectButton->OnClicked.RemoveDynamic(this, &UTRAbilityList::ClickSelectButton);
	SelectButton->OnClicked.AddDynamic(this, &UTRAbilityList::ClickSelectButton);

	WO = Cast<UWeapon1Object>(ListItemObject);

	TextName->SetText(FText::FromString(FString(WO->AbilityObject.name)));
	TextCoolDown->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->AbilityObject.useCooldown)));
	TextDuration->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->AbilityObject.activeTime)));
	//TextbBuff->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.cost)));
	TextWeight->SetText(FText::FromString(FString::FromInt(WO->AbilityObject.weight)));
	TextCost->SetText(FText::FromString(FString::FromInt(WO->AbilityObject.cost)));

	Ability = WO->_RowName;

	if (WO->bIsEquiped)
	{
		TextBlock_true->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		TextBlock_true->SetVisibility(ESlateVisibility::Hidden);
	}
	indexNum = WO->indexNum;
}

void UTRAbilityList::ClickSelectButton()
{
	UTestRoomSetWidget* TRSW = Cast<UTestRoomSetWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (TRSW)
	{
		TRSW->gearRowName = Ability;
		TRSW->ResetEuqipState(3, indexNum);
	}

	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (TRGM->enemyREF)
	{
		TRGM->enemyREF->ChangeGear(Ability);
		TRGM->enemyREF->CheakWeightLimit();
	}
	if (TRSW)
	{
		//금액갱신
		TRSW->UpdateMonsterCost();
		TRSW->SetEnemySpec(3, Ability);
	}
}
