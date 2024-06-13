// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "HideAndSeekGameInstance.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Slider.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableText.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetSwitcher.h>
#include "RoomInfoUI.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>

void ULobbyWidget::NativeConstruct()
{
	// ���� �ν��Ͻ� ä���
	gi = Cast<UHideAndSeekGameInstance>(GetWorld()->GetGameInstance());

	// gi�� OnMySessionSearchCompleteDelegate�� AddRoomInfoUI�� �����ϰ�ʹ�.
	gi->OnMySessionSearchCompleteDelegate.AddDynamic(this, &ULobbyWidget::AddRoomInfoUI);

	// gi�� OnMySessionSearchFinishedDelegate�� OnMySetActiveFindingText�� �����Ѵ�
	gi->OnMySessionSearchFinishedDelegate.AddDynamic(this, &ULobbyWidget::OnMySetActiveFindingText);

	// ��ư ����
	Button_CreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickCreateRoom);
	Slider_PlayerCount->SetValue(FCString::Atof(*Text_PlayerCounts->GetText().ToString()));

	Button_GoCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickGoCreateRoom);
	Button_GoFindRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickGoFindRoom);

	Button_Menu->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickGoMenu);
	Button_OutMenu->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickGoMenu);

	Button_Find->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClickFindRoom);

	// �����̴� ����
	Slider_PlayerCount->OnValueChanged.AddDynamic(this, &ULobbyWidget::OnMyValueChanged);

	// ���� ���۽� �޴����� Ȱ��ȭ
	SwitcherUI->SetActiveWidgetIndex(0);
}

void ULobbyWidget::OnMyClickCreateRoom()
{
	// ���� �ν��Ͻ��� �ִٸ�
	if (gi)
	{
		// �÷��̾��� ���ڸ� �޾ƿ´�
		int32 count = Slider_PlayerCount->GetValue();
		// �޾ƿ� �÷��̾��� ���ڴ��
		gi->CreateMySession(Edit_RoomName->GetText().ToString(), count);

	}
}

void ULobbyWidget::OnMyValueChanged(float value)
{
	Text_PlayerCounts->SetText(FText::AsNumber(value));
}

void ULobbyWidget::OnMyClickGoMenu()
{
	SwitcherUI->SetActiveWidgetIndex(0);
}
void ULobbyWidget::OnMyClickGoCreateRoom()
{	
	//�г��� ����
	SetSessionName();
		
	SwitcherUI->SetActiveWidgetIndex(1);
}
void ULobbyWidget::OnMyClickGoFindRoom()
{
	// �г��� ����
	SetSessionName();

	SwitcherUI->SetActiveWidgetIndex(2);

	// �� ã�� �޴� ���Խ� �� ã�� �õ�
	if (gi)
	{
		gi->FindOtherSessions();
	}
}

void ULobbyWidget::OnMyClickFindRoom()
{
	// ���� ��� ����
	ScrollBox_RoomList->ClearChildren();
	
	// gi�� FindOtherSession ȣ��
	gi->FindOtherSessions();
}

void ULobbyWidget::AddRoomInfoUI(const struct FSessionInfo& info)
{
	// RoomInfoUI_BP�� �̿��� ���� �����
	auto ui = CreateWidget<URoomInfoUI>(this, roomInfoUI_BP);
	// info�� Setup�Լ��� ���� ����
	ui->Setup(info);
	// ������ ������ scrollBox_RoomList�� ���̱�
	ScrollBox_RoomList->AddChild(ui);
}

void ULobbyWidget::OnMySetActiveFindingText(bool bSearching)
{
	Text_Finding->SetVisibility(bSearching ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Button_Find->SetIsEnabled(bSearching);
}

void ULobbyWidget::SetSessionName()
{
	if (gi)
	{
		// �ν��Ͻ����� MySessionName(�г���)�� �����ͼ� Edit_SessionName�� �����Ѵ�.
		gi->mySessionName = Edit_SessionName->GetText().ToString();
	}
}
