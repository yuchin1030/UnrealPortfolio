#include "BJK/LoadWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>



void ULoadWidget::NativeConstruct()
{
	// ������ ��� �ޱ�
	Button_Destroy->OnClicked.AddDynamic(this, &ULoadWidget::OnClickDestroy);
	Button_Quit->OnClicked.AddDynamic(this, &ULoadWidget::OnClickQuit);
	Button_Load->OnClicked.AddDynamic(this, &ULoadWidget::OnClickLoad);
}

void ULoadWidget::OnClickDestroy()
{
	// ���� ĳ���� ����
}

void ULoadWidget::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULoadWidget::OnClickLoad()
{
	// ���� ������ �̵�
}
