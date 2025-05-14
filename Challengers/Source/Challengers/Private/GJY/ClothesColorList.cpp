// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/ClothesColorList.h"
#include "GJY/CreatorTestCharacter.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GJY/PlayerCustomizer.h"
#include "GJY/ColorStruct.h"

void UClothesColorList::NativeConstruct()
{
	Super::NativeConstruct();

	SelectButton->OnClicked.AddDynamic(this, &UClothesColorList::ClickSelectButton);
}

void UClothesColorList::ClickSelectButton()
{
	CC = Cast<ACreatorTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	if (CS->PC)
	{
		if (CC)
		{
			CC->ClothesColorChange(CS->RowNumber);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CC Null"));
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PC Null"));

}
