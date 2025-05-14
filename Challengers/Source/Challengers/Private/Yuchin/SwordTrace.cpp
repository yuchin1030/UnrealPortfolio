// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/SwordTrace.h"
#include "Sword.h"
#include "ChallengersCharacter.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void USwordTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	player = Cast<AChallengersCharacter>(MeshComp->GetOwner());

	if (player)
	{
		if (player->sword) {
			player->sword->StartSwordTrace(player->currentSkillNum);
		}
	}
}

void USwordTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	player = Cast<AChallengersCharacter>(MeshComp->GetOwner());

	if (player)
	{
		if (player->sword) {
			player->sword->StopSwordTrace();
		}
	}
}
