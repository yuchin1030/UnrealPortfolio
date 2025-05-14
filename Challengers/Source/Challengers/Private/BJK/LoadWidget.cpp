#include "BJK/LoadWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>



void ULoadWidget::NativeConstruct()
{
	// 아이템 모두 받기
	Button_Destroy->OnClicked.AddDynamic(this, &ULoadWidget::OnClickDestroy);
	Button_Quit->OnClicked.AddDynamic(this, &ULoadWidget::OnClickQuit);
	Button_Load->OnClicked.AddDynamic(this, &ULoadWidget::OnClickLoad);
}

void ULoadWidget::OnClickDestroy()
{
	// 기존 캐릭터 삭제
}

void ULoadWidget::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULoadWidget::OnClickLoad()
{
	// 마을 레벨로 이동
}
