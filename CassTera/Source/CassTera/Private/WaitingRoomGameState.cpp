// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomGameState.h"
#include "WaitingRoomTimerWidget.h"
#include "ChatWidget.h"
#include "Net/UnrealNetwork.h"

void AWaitingRoomGameState::BeginPlay()
{
	Super::BeginPlay();

	// Ÿ�̸� ui�� �����ϰ�
	if (WaitingTimerUI_BP)
	{
		WaitingTimerUI = Cast< UWaitingRoomTimerWidget>(CreateWidget(GetWorld(), WaitingTimerUI_BP));

		// ����Ʈ�� ������
		WaitingTimerUI->AddToViewport();
	}
	
}	


void AWaitingRoomGameState::ServerRPC_SetTimer_Implementation(float DeltaSeconds)
{
	// ���ӽ��� Ÿ�̸� ������
	float sec = StartTimer - DeltaSeconds;
	sec = FMath::Clamp(sec, 0, StartTimer);

	// Ŭ���̾�Ʈ�� �ð� ����ȭ
	MultiRPC_SetTimer(sec);
}

void AWaitingRoomGameState::MultiRPC_SetTimer_Implementation(float second)
{	
	StartTimer = second;
	if (WaitingTimerUI)
	{
		WaitingTimerUI->TimerSet();
		// ���� ������Ʈ���� Ÿ�̸� ui ���� �� ����Ʈ �߰�
		// ���� ������Ʈ���� ����rpc�� �ð� ���� ��� �����
		// �ð� ���� ����RPC�� ��Ʈ�ѷ��� Tick���� ȣ��
		// ����RPC�� ��ƼRPC�� ����
		// ��ƼRPC���� �ð� ����ȭ �� Ÿ�̸� UI�� ���� �ݿ�
	}
}


