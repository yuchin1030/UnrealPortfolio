// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/ListViewItem/TRWeaponList1.h"
#include "CHR/TestRoomGameMode.h"
#include "CHR/TestRoomSetWidget.h"
#include "CHR/WeaponStruct.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ListViewBase.h"
#include "GJY/Weapon1Object.h"
#include "CHR/BaseEnemy.h"
#include "OurGameInstance.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UTRWeaponList1::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectButton->OnClicked.RemoveDynamic(this, &UTRWeaponList1::ClickSelectButton);
	SelectButton->OnClicked.AddDynamic(this, &UTRWeaponList1::ClickSelectButton);

	WO = Cast<UWeapon1Object>(ListItemObject);


	NameText->SetText(FText::FromString(FString(WO->WeaponObject1.name)));
	DamageText->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.damage)));

	RangeText->SetVisibility(ESlateVisibility::Visible);
	Image_Text->SetVisibility(ESlateVisibility::Hidden);

	if (WO->WeaponObject1.attackRange == 150)
	{
		RangeText->SetVisibility(ESlateVisibility::Hidden);
		Image_Text->SetVisibility(ESlateVisibility::Visible);
	}
	else
		RangeText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->WeaponObject1.attackRange)));

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

void UTRWeaponList1::ClickSelectButton()
{
	UTestRoomSetWidget* TRSW = Cast<UTestRoomSetWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (TRSW)
	{
		TRSW->weapon1RowName = Weapon;
		TRSW->ResetEuqipState(1, indexNum);
	}

	ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (TRGM->enemyREF)
	{
		TRGM->enemyREF->ChangeWeapon1(Weapon);
		TRGM->enemyREF->CheakWeightLimit();
	}
	if (TRSW)
	{
		//금액갱신
		TRSW->UpdateMonsterCost();
		TRSW->SetEnemySpec(1, Weapon);
	}
}
