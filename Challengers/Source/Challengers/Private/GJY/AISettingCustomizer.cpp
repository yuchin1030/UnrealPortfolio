// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/AISettingCustomizer.h"
#include "GJY/EnemyCustomizer.h"
#include "GJY/CustomModeBase.h"
#include "CHR/BaseEnemy.h"
#include "OurGameInstance.h"
#include "MainPlayerController.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"



void UAISettingCustomizer::NativeConstruct()
{
	CM = Cast<ACustomModeBase>(GetWorld()->GetAuthGameMode());

	AISettingSwitcher->SetActiveWidgetIndex(0);
	AICancelBtn->OnClicked.AddDynamic(this, &UAISettingCustomizer::ClickCancelButton);
	AISaveBtn->OnClicked.AddDynamic(this, &UAISettingCustomizer::ClickSaveButton);
	SaveYesButton->OnClicked.AddDynamic(this, &UAISettingCustomizer::FinalSaveYes);
	SaveNoButton->OnClicked.AddDynamic(this, &UAISettingCustomizer::FinalSaveNo);


	Button_1->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered1);
	Button_2->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered2);
	Button_3->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered3);
	Button_4->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered4);
	Button_5->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered5);
	Button_6->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered6);
	Button_7->OnHovered.AddDynamic(this, &UAISettingCustomizer::OnHovered7);

	Button_1->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered1);
	Button_2->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered2);
	Button_3->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered3);
	Button_4->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered4);
	Button_5->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered5);
	Button_6->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered6);
	Button_7->OnUnhovered.AddDynamic(this, &UAISettingCustomizer::OnUnhovered7);


}

void UAISettingCustomizer::ClickSaveButton()
{
	for (TActorIterator<ABaseEnemy> it(GetWorld()); it; ++it)
	{
		Enemy = *it;
	}

	if (Enemy)
	{
		//세팅한 AI 세팅 값을 넘겨준다.
		Enemy -> AIData.battleDist = BattleDistSlide->GetValue();
		UE_LOG(LogTemp, Warning,TEXT("%f"),Enemy->AIData.battleDist);
		Enemy -> AIData.randomArea = RandomAreaSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.randomArea);
		Enemy -> AIData.moveRate = MoveRateSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.moveRate);
		Enemy -> AIData.playerFindDist = PlayerFindDistSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.playerFindDist);
		Enemy -> AIData.targetChangeRate = TargetChangeRateSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.targetChangeRate);
		Enemy -> AIData.phase2Rate = Phase2RateSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.phase2Rate);
		Enemy -> AIData.phase3Rate = Phase3RateSlide->GetValue();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Enemy->AIData.phase3Rate);
		if (Enemy->AIData.phase2Rate <= Enemy->AIData.phase3Rate) {
			Enemy->AIData.phase3Rate = Enemy->AIData.phase2Rate - 0.1;
		}
	}


	//마지막으로 저장할 것인지 물어보는 UI를 띄운다.
	AISettingSwitcher->SetActiveWidgetIndex(1);

}

void UAISettingCustomizer::ClickCancelButton()
{	
	//EnemyCustomizer UI를 다시 띄운다.
	CM->ShowEnemyCustomizer();
	SetVisibility(ESlateVisibility::Hidden);
}

void UAISettingCustomizer::FinalSaveYes()
{
	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	OG->bSLoading = true;
	

	FString EnemyName = InputEnemyName->GetText().ToString();


	OG->SaveEnemyData(EnemyName , Enemy->enemySpec.bIsBossType, Enemy->enemySpec.totalCost, Enemy->bodyRowName, Enemy->weapon1RowName, Enemy->weapon2RowName, Enemy->gearRowName, Enemy->AIData);

	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		pc->SetInputMode(FInputModeGameOnly());
	}

	CM->ShowEnemyCustomizer();
	SetVisibility(ESlateVisibility::Hidden);

	CM->Enemy_Inst->SaveComplete();

}

void UAISettingCustomizer::FinalSaveNo()
{
	AISettingSwitcher->SetActiveWidgetIndex(0);
}


// 아이콘 위의 버튼에 마우스 올릴 시 설명 나오는 버튼들
void UAISettingCustomizer::OnHovered1()
{
	Image_1->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered1()
{
	Image_1->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered2()
{
	Image_2->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered2()
{
	Image_2->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered3()
{
	Image_3->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered3()
{
	Image_3->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered4()
{
	Image_4->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered4()
{
	Image_4->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered5()
{
	Image_5->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered5()
{
	Image_5->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered6()
{
	Image_6->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered6()
{
	Image_6->SetVisibility(ESlateVisibility::Hidden);
}



void UAISettingCustomizer::OnHovered7()
{
	Image_7->SetVisibility(ESlateVisibility::Visible);
}

void UAISettingCustomizer::OnUnhovered7()
{
	Image_7->SetVisibility(ESlateVisibility::Hidden);
}
