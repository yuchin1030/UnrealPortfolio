#include "BJK/SelectCCWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "GJY/PlayerCustomizer.h"


void USelectCCWidget::NativeConstruct()
{	
	// ������ ��� �ޱ�
	Button_Yes->OnClicked.AddDynamic(this, &USelectCCWidget::OnClickYes);
	Button_No->OnClicked.AddDynamic(this, &USelectCCWidget::OnClickNo);
}

void USelectCCWidget::OnClickYes()
{
	// ������ �������� ����

	UGameplayStatics::OpenLevel(GetWorld(),"BodyChangeTest");
}

void USelectCCWidget::OnClickNo()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	SetVisibility(ESlateVisibility::Hidden);
}
