#include "BJK/CheckPointWidget.h"
#include "OurGameModeBase.h"
#include "GJY/CustomModeBase.h"
#include "Yohan/DungeonEditGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Yohan/DungeonEditCharacter.h"
#include "Yohan/DungeonEditComponent.h"
#include "Yohan/OurGameStateBase.h"
#include "OurGameInstance.h"
#include "MainPlayerController.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>

void UCheckPointWidget::NativeConstruct()
{

	OGM = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
	CGM = Cast<ACustomModeBase>(GetWorld()->GetAuthGameMode());
	DGM = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode());
	GI = Cast<UOurGameInstance>(GetGameInstance());
	OGS = Cast<AOurGameStateBase>(GetWorld()->GetGameState());

	
	if (OGM) {
		OGM->loadingEndDelegate.BindUFunction(this, FName("ShowMapname"));
	}

	if (CGM) {
		CGM->loadingEndDelegate.BindUFunction(this, FName("ShowMapname"));
	}

	if (DGM) {
		ADungeonEditCharacter* DEC = Cast<ADungeonEditCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (DEC)
		{
			UDungeonEditComponent* DECC = DEC->FindComponentByClass<UDungeonEditComponent>();
			if (DECC)
			{
				DECC->loadingEndDelegate.BindUFunction(this, FName("ShowMapname"));
			}
		}
	}

	if (GI) {
		GI->loadingEndDelegate.BindUFunction(this, FName("ShowMapname"));
	}

	if (OGS) {
		OGS->loadingEndDelegate.BindUFunction(this, FName("ShowMapname"));
	}
}

void UCheckPointWidget::ShowMapname()
{
	if (!Test)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowMapname called"));

		// 마을로 돌아 올 시에 나오는 문구 애니메이션
		if (GetWorld()->GetMapName().Contains("SingleMap"))
		{
	
			Image_C->SetVisibility(ESlateVisibility::Visible);
			Image_A->SetVisibility(ESlateVisibility::Hidden);
			Image_B->SetVisibility(ESlateVisibility::Hidden);

			UUserWidget::PlayAnimation(CheckAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
			Test =true;
		}

		// 몬스터 커스터 마이징에 입장 시에 나오는 문구 애니메이션
		if (GetWorld()->GetMapName().Contains("TestRoom"))
		{
			Image_C->SetVisibility(ESlateVisibility::Hidden);
			Image_A->SetVisibility(ESlateVisibility::Visible);
			Image_B->SetVisibility(ESlateVisibility::Hidden);

			UUserWidget::PlayAnimation(TestRoomAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
			Test = true;
		}

		// 멀티방에 입장 시에 나오는 문구 애니메이션
		if (GetWorld()->GetMapName().Contains("MultipMap"))
		{
			Image_C->SetVisibility(ESlateVisibility::Hidden);
			Image_A->SetVisibility(ESlateVisibility::Hidden);
			Image_B->SetVisibility(ESlateVisibility::Visible);

			UUserWidget::PlayAnimation(MultiANim, 0, 1, EUMGSequencePlayMode::Forward, 1);
			Test = true;
		}
		else
		{
			Image_C->SetVisibility(ESlateVisibility::Hidden);
			Image_A->SetVisibility(ESlateVisibility::Hidden);
			Image_B->SetVisibility(ESlateVisibility::Hidden);
			Test = true;
		}

	}
	

}


