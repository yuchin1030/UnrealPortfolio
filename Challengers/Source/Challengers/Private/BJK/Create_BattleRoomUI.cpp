#include "BJK/Create_BattleRoomUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OurGameInstance.h"

void UCreate_BattleRoomUI::NativeConstruct()
{
	Button_Join->OnClicked.AddDynamic(this, &UCreate_BattleRoomUI::OnClickJoinRoom);
}

void UCreate_BattleRoomUI::OnClickJoinRoom()
{
	// �÷��̾ ���� ������ ����
}


