#include "GJY/PlayerCustomizer.h"
#include "Components/Button.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include "GJY/CreatorTestCharacter.h"
#include "MainPlayerController.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableText.h>
#include "Components/WidgetSwitcher.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include "GJY/MaterialStruct.h"
#include "GJY/Weapon1Object.h"
#include "GJY/ColorStruct.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/UniformGridPanel.h>
#include "GJY/FrontHairColorList.h"
#include "GJY/ClothesColorList.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/UniformGridSlot.h>
#include "Components/Image.h"


#define MOVETIME 0.7f

void UPlayerCustomizer::NativeConstruct()
{
	Super::NativeConstruct();

	CharCumaSwitcher->SetActiveWidgetIndex(0);
	ColorSwitcherUI->SetActiveWidgetIndex(0);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Hidden);

	Image_10->SetVisibility(ESlateVisibility::Hidden);

	HairLeftButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::HairDownBtn);
	HairRightButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::HairUPBtn);

	ClothesLeftButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::ClothesDownBtn);
	ClothesRightButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::ClothesUpBtn);

	GlovesLeftButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::GlovesDownBtn);
	GlovesRightButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::GlovesUpBtn);
	BoyButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::SelectBoy);
	GirlButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::SelectGirl);

	Button_Yes->OnClicked.AddDynamic(this, &UPlayerCustomizer::CharacterCreate);
	Button_No->OnClicked.AddDynamic(this, &UPlayerCustomizer::CharacterCancel);
	StartButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::GameStartBtn);

	HairColorChangeButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::HairChangeColor);
	ClothesColorChangeButton->OnClicked.AddDynamic(this, &UPlayerCustomizer::ClothesChangeColor);

	/*CC = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));*/
	CC = Cast<ACreatorTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

}

void UPlayerCustomizer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(bCameraMoving1)
	{
		CC->FollowCamera->SetRelativeLocation(FMath::InterpEaseOut(Start, End, GetWorld()->GetTimerManager().GetTimerElapsed(alpha) / MOVETIME, Speed));
		CC->FollowCamera->SetFieldOfView(FMath::InterpEaseOut(90.0f, 50.0f, GetWorld()->GetTimerManager().GetTimerElapsed(alpha) / MOVETIME, Speed));
	}

	if(bCameraMoving2)
	{
		CC->FollowCamera->SetRelativeLocation(FMath::InterpEaseOut(End, Start, GetWorld()->GetTimerManager().GetTimerElapsed(alpha) / MOVETIME, Speed));
		CC->FollowCamera->SetFieldOfView(FMath::InterpEaseOut(50.0f, 90.0f, GetWorld()->GetTimerManager().GetTimerElapsed(alpha) / MOVETIME, Speed));
	}
}

void UPlayerCustomizer::HairUPBtn()
{
	if (CC != nullptr)
	{
		CC->HairIndex++;

		CC->HairIndex %= 6;
		CC->ChangeHair();
	}

	MovingCamera();

}

void UPlayerCustomizer::HairDownBtn()
{
	CC->HairIndex--;

	if (CC->HairIndex < 0)
	{
		CC->HairIndex = 5;
	}
	CC->ChangeHair();

	MovingCamera();

}

void UPlayerCustomizer::ClothesUpBtn()
{
	CC->ClothesIndex++;

	CC->ClothesIndex %= 2;
	CC->ChangeClothes();

	ReturnCamera();

}

void UPlayerCustomizer::ClothesDownBtn()
{
	CC->ClothesIndex--;

	if (CC->ClothesIndex < 0)
	{
		CC->ClothesIndex = 1;
	}
	CC->ChangeClothes();

	ReturnCamera();

}

void UPlayerCustomizer::GlovesUpBtn()
{
	CC->GlovesIndex++;

	CC->GlovesIndex %= 2;
	CC->ChangeGloves();

	Image_10->SetVisibility(ESlateVisibility::Hidden);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Hidden);


	ReturnCamera();
}

void UPlayerCustomizer::GlovesDownBtn()
{
	CC->GlovesIndex--;

	if (CC->GlovesIndex < 0)
	{
		CC->GlovesIndex = 1;
	}
	CC->ChangeGloves();
	
	Image_10->SetVisibility(ESlateVisibility::Hidden);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Hidden);

	ReturnCamera();
}

void UPlayerCustomizer::SelectBoy()
{
	Image_10->SetVisibility(ESlateVisibility::Hidden);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Hidden);

	CC->bBoy = true;
	CC->SelectBoy();


}

void UPlayerCustomizer::SelectGirl()
{
	Image_10->SetVisibility(ESlateVisibility::Hidden);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Hidden);

	CC->bBoy = false;
	CC->SelectGirl();

}

void UPlayerCustomizer::GameStartBtn()
{
	NickName = InputNickName->GetText().ToString();

	if(NickName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("NickName is Null"));
	}
	else
	{ 
		CharCumaSwitcher->SetActiveWidgetIndex(1); 

		TextBlock_PlayerName->SetText(FText::FromString(NickName));
	}
}


void UPlayerCustomizer::CharacterCreate()
{

	CC->LoadArray();
	OG->SaveChracterCustom(CC->bBoy, CC->FinalMeshArr, NickName, CC->ClothesNum, CC->HairNum , CC->bGlove);

	TArray<int32> newWeaponLevel = {1,1,1};
	TArray<int32> newWeaponStat = { 30, 30, 30 };
	TArray<int32> newNextWeaponStat = { 31, 31, 31 };
	TArray<int32> newUpgNeedGold = { 100, 100, 100 };
	

	OG->SavePlayerInfoData(NickName, 1, 10000000, 0, 1000, 500, newWeaponLevel, newWeaponStat, newNextWeaponStat, newUpgNeedGold);

	/*UE_LOG(LogTemp, Warning, TEXT("CharacterCreate Save :: newWeaponLevel[0] : %d, currentWeaponStat[0] : %d, nextWeaponStat[0] : %d, upgWeaponNeedGold : %d"), newWeaponLevel[0], newWeaponStat[0], newNextWeaponStat[0], newUpgNeedGold[0]);
	UE_LOG(LogTemp, Warning, TEXT("CharacterCreate Save :: newWeaponLevel[1] : %d, currentWeaponStat[1] : %d, nextWeaponStat[1] : %d, upgWeaponNeedGold : %d"), newWeaponLevel[1], newWeaponStat[1], newNextWeaponStat[1], newUpgNeedGold[1]);
	UE_LOG(LogTemp, Warning, TEXT("CharacterCreate Save :: newWeaponLevel[2] : %d, currentWeaponStat[2] : %d, nextWeaponStat[2] : %d, upgWeaponNeedGold : %d"), newWeaponLevel[2], newWeaponStat[2], newNextWeaponStat[2], newUpgNeedGold[2]);*/

	TArray<int32> newSkillLevel = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	OG->SaveSkillPresetData(NickName, newSkillLevel, 30);

	OG->bSLoading = true;
	//UGameplayStatics::OpenLevel(GetWorld(), "SingleMap");
}


void UPlayerCustomizer::CharacterCancel()
{
	CharCumaSwitcher->SetActiveWidgetIndex(0);
}

void UPlayerCustomizer::HairChangeColor()
{
	Image_10->SetVisibility(ESlateVisibility::Visible);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Visible);
	ColorSwitcherUI->SetActiveWidgetIndex(0);
	HairColorSelect();
}


void UPlayerCustomizer::ClothesChangeColor()
{
	Image_10->SetVisibility(ESlateVisibility::Visible);
	ColorSwitcherUI->SetVisibility(ESlateVisibility::Visible);
	ColorSwitcherUI->SetActiveWidgetIndex(1);
	ClothesColorSelect();
}


void UPlayerCustomizer::MovingCamera()
{
	if(bCanReturnCamera == false)
	{ 
		if (!bIsZoom)
		{
			GetWorld()->GetTimerManager().SetTimer(alpha, FTimerDelegate::CreateLambda([&]() {
				bCameraMoving1 = false;
				bCanReturnCamera = true;
				}), MOVETIME, false);
			bCameraMoving1 = true;
			bIsZoom = true;
		}
	
	}
}

void UPlayerCustomizer::ReturnCamera()
{
	if(bCanReturnCamera == true)
	{
		if (bIsZoom)
		{
			GetWorld()->GetTimerManager().SetTimer(alpha, FTimerDelegate::CreateLambda([&]() {
				bCameraMoving2 = false;
				bCanReturnCamera = false;
				}), MOVETIME, false);
			bCameraMoving2 = true;
			bIsZoom = false;
		}
	
	}
}

void UPlayerCustomizer::HairColorSelect()
{
	hairGridPanel->ClearChildren();

	HairColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));

	TArray<FMaterialType*> MaterialData;

	HairColorDataTable->GetAllRows<FMaterialType>(TEXT("GetAllRows"), MaterialData);

	for (int32 i = 0; i < 6; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			UFrontHairColorList* hairColorItem = CreateWidget<UFrontHairColorList>(this, hairColor_bp);

			if (hairColorItem)
			{
				UColorStruct* _CS = NewObject<UColorStruct>(this, UColorStruct::StaticClass());
				if (_CS)
				{
					_CS->PC = this;
					_CS->RowNumber = i * 4 + j;
					_CS->MaterialObject = *MaterialData[i * 4 + j];

					hairColorItem->CS = _CS;
					hairColorItem->img_BtnColor->SetBrushFromTexture(MaterialData[i * 4 + j]->ColorUI);

					UUniformGridSlot* item = hairGridPanel->AddChildToUniformGrid(hairColorItem, i, j);

					item->SetHorizontalAlignment(HAlign_Fill);
					item->SetVerticalAlignment(VAlign_Fill);
				}
			}
		}
	}
}

void UPlayerCustomizer::ClothesColorSelect()
{	
	ClothesGridPanel->ClearChildren();
	if(CC->bBoy == false)
	{
		ClothesColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_F.ClothesColorDataTable_F'"));
	}
	else
	{
		ClothesColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_M.ClothesColorDataTable_M'"));
	}

	TArray<FMaterialType*> MaterialData2;

	ClothesColorDataTable->GetAllRows<FMaterialType>(TEXT("GetAllRows"), MaterialData2);

	for (int32 i = 0; i < 6; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			if (i * 4 + j >= MaterialData2.Num())
			{
				return;
			}

			UClothesColorList* clothesColorItem = CreateWidget<UClothesColorList>(this, clothesColor_bp);

			if (clothesColorItem)
			{
				UColorStruct* _CS = NewObject<UColorStruct>(this, UColorStruct::StaticClass());
				if (_CS)
				{
					_CS->PC = this;
					_CS->RowNumber = i * 4 + j;
					_CS->MaterialObject2 = *MaterialData2[i * 4 + j];

					clothesColorItem->CS = _CS;
					clothesColorItem->img_BtnColor->SetBrushFromTexture(MaterialData2[i * 4 + j]->ColorUI);

					UUniformGridSlot* item = ClothesGridPanel->AddChildToUniformGrid(clothesColorItem, i, j);

					item->SetHorizontalAlignment(HAlign_Fill);
					item->SetVerticalAlignment(VAlign_Fill);
				}
			}
		}
	}
}