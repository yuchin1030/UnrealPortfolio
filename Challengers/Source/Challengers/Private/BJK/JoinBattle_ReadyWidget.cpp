#include "BJK/JoinBattle_ReadyWidget.h"
#include "Components/Button.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


void UJoinBattle_ReadyWidget::NativeConstruct()
{
	Button_Ready->OnClicked.AddDynamic(this, &UJoinBattle_ReadyWidget::OnClickReady);
	Button_Quit->OnClicked.AddDynamic(this, &UJoinBattle_ReadyWidget::OnClickQuit);
}


// �����غ� ��ư
void UJoinBattle_ReadyWidget::OnClickReady()
{
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->ClientTravel("/All/Game/BJK/Maps", ETravelType::TRAVEL_Absolute);
}
// ������ ��ư
void UJoinBattle_ReadyWidget::OnClickQuit()
{
	
}
