#include "BJK/SelectCCWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "GJY/PlayerCustomizer.h"


void USelectCCWidget::NativeConstruct()
{	
	// 아이템 모두 받기
	Button_Yes->OnClicked.AddDynamic(this, &USelectCCWidget::OnClickYes);
	Button_No->OnClicked.AddDynamic(this, &USelectCCWidget::OnClickNo);
}

void USelectCCWidget::OnClickYes()
{
	// 저장한 내용으로 시작

	UGameplayStatics::OpenLevel(GetWorld(),"BodyChangeTest");
}

void USelectCCWidget::OnClickNo()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	SetVisibility(ESlateVisibility::Hidden);
}
