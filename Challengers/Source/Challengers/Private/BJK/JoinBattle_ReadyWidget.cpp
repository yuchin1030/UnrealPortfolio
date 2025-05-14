#include "BJK/JoinBattle_ReadyWidget.h"
#include "Components/Button.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


void UJoinBattle_ReadyWidget::NativeConstruct()
{
	Button_Ready->OnClicked.AddDynamic(this, &UJoinBattle_ReadyWidget::OnClickReady);
	Button_Quit->OnClicked.AddDynamic(this, &UJoinBattle_ReadyWidget::OnClickQuit);
}


// 전투준비 버튼
void UJoinBattle_ReadyWidget::OnClickReady()
{
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->ClientTravel("/All/Game/BJK/Maps", ETravelType::TRAVEL_Absolute);
}
// 나가기 버튼
void UJoinBattle_ReadyWidget::OnClickQuit()
{
	
}
