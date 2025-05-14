// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/AbilityList.h"
#include "CHR/BaseEnemy.h"
#include "EngineUtils.h"
#include "OurGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GJY/Weapon1Object.h"


void UAbilityList::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectButton->OnClicked.AddDynamic(this, &UAbilityList::ClickSelectButton);

	WO = Cast<UWeapon1Object>(ListItemObject);

	TextName->SetText(FText::FromString(FString(WO->AbilityObject.name)));
	TextCoolDown->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->AbilityObject.useCooldown)));
	TextDuration->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), WO->AbilityObject.activeTime)));
	//TextbBuff->SetText(FText::FromString(FString::FromInt(WO->WeaponObject1.cost)));
	TextWeight->SetText(FText::FromString(FString::FromInt(WO->AbilityObject.weight)));
	TextCost->SetText(FText::FromString(FString::FromInt(WO->AbilityObject.cost)));

	Ability = WO->_RowName;
}

void UAbilityList::ClickSelectButton()
{
	UOurGameInstance* OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());;
	//버튼을 클릭하면 그 해당하는 데이터를 에너미에게 입혀주고싶다.

	for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		Enemy = *it;
	}
	
	Enemy->ChangeGear(Ability);
}
