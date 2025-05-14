// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/ListViewItem/TRWeaponList2.h"
#include "CHR/TestRoomGameMode.h"
#include "CHR/TestRoomSetWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ListViewBase.h"
#include "GJY/Weapon1Object.h"
#include "CHR/BaseEnemy.h"
#include "OurGameInstance.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UTRWeaponList2::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectButton->OnClicked.RemoveDynamic(this, &UTRWeaponList2::ClickSelectButton);
	SelectButton->OnClicked.AddDynamic(this, &UTRWeaponList2::ClickSelectButton);

	WO = Cast<UWeapon1Object>(ListItemObject);

	NameText->SetText(FText::FromString(FString(WO->WeaponObject1.name)));
	DamageText->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.damage)));

	RangeText->SetVisibility(ESlateVisibility::Visible);
	Image_Text->SetVisibility(ESlateVisibility::Hidden);

	RangeText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->WeaponObject1.attackRange)));
	if (WO->WeaponObject1.attackRange <= 150.0f)
	{
		RangeText->SetVisibility(ESlateVisibility::Hidden);
		Image_Text->SetVisibility(ESlateVisibility::Visible);
	}

	CostText->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.cost)));
	WeightText->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.weight)));

	Weapon = WO->_RowName;

	if (WO->bIsEquiped)
	{
		TextBlock_true->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		TextBlock_true->SetVisibility(ESlateVisibility::Hidden);
	}
	indexNum = WO->indexNum;
}

void UTRWeaponList2::ClickSelectButton()
{
	UTestRoomSetWidget* TRSW = Cast<UTestRoomSetWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (TRSW)
	{
		TRSW->weapon2RowName = Weapon;
		TRSW->ResetEuqipState(2, indexNum);
	}

	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (TRGM->enemyREF)
	{
		TRGM->enemyREF->ChangeWeapon2(Weapon);
		TRGM->enemyREF->CheakWeightLimit();
	}
	if (TRSW)
	{
		//금액갱신
		TRSW->UpdateMonsterCost();
		TRSW->SetEnemySpec(2, Weapon);
	}
}
