// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/BodyList.h"
#include "GJY/Weapon1Object.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "OurGameInstance.h"
#include "EngineUtils.h"
#include "SkillStruct.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UBodyList::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	//gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	WO = Cast<UWeapon1Object>(ListItemObject);

	SelectButton->OnClicked.AddDynamic(this, &UBodyList::ClickSelectButton);
	
	HPText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.HP)));
	WeightText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.weightLimit)));
	CostText->SetText(FText::FromString(FString::FromInt(WO->BodyObject.cost)));
	NameText->SetText(FText::FromString(WO->BodyObject.name));
	
	if(WO->BodyObject.bIsBossType)
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

}

void UBodyList::ClickSelectButton()
{

	UOurGameInstance* OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());;
	//��ư�� Ŭ���ϸ� �� �ش��ϴ� �����͸� ���ʹ̿��� �����ְ�ʹ�.

	for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		Enemy = *it;
	}

	Enemy->ChangeBody(Body);



}
