#include "GJY/WeaponList1.h"
#include "CHR/WeaponStruct.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GJY/Weapon1Object.h"
#include "CHR/BaseEnemy.h"
#include "OurGameInstance.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


void UWeaponList1::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	SelectButton->OnClicked.RemoveDynamic(this, &UWeaponList1::ClickSelectButton);
	SelectButton->OnClicked.AddDynamic(this, &UWeaponList1::ClickSelectButton);
	
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
}



void UWeaponList1::ClickSelectButton()
{
	UOurGameInstance* OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());;
	//버튼을 클릭하면 그 해당하는 데이터를 에너미에게 입혀주고싶다.
	
	for(TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		Enemy = *it;
	}

	Enemy->ChangeWeapon1(Weapon);
}
