// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/PlayerAnimInstance.h"
#include "ChallengersCharacter.h"
#include "../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerREF = Cast<AChallengersCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::AnimNotify_Player_AtkEnd()
{
	if (playerREF)
	{
		playerREF->Anim_AtkEnd();
	}
}

void UPlayerAnimInstance::AnimNotify_PlusMP()
{
	if (playerREF)
	{
		playerREF->MP += 5;
	}
}

void UPlayerAnimInstance::AnimNotify_CanAttackAgain()
{
	if (playerREF)
	{
		playerREF->bCanSwordBasicAttack = true;
	}
}

void UPlayerAnimInstance::AnimNotify_CanWandBsAttackAgain()
{
	if (playerREF)
	{
		playerREF->bCanWandBasicAttack = true;
		playerREF->bSkillUsing = false;
	}
}

void UPlayerAnimInstance::AnimNotify_SpawnWand3()
{
	if (playerREF)
	{
		playerREF->SpawnWand3();
	}
}

void UPlayerAnimInstance::AnimNotify_SpawnArrowBasic()
{
	if (playerREF)
	{
		playerREF->SpawnArrowBasic();
		UGameplayStatics::PlaySound2D(GetWorld(), playerREF->bowBasicSound);
	}
}

void UPlayerAnimInstance::AnimNotify_SpawnArrow1()
{
	if (playerREF)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawn arrow1"));
		playerREF->SpawnArrow1();
		UGameplayStatics::PlaySound2D(GetWorld(), playerREF->bowSkill1Sound);
	}
}

void UPlayerAnimInstance::AnimNotify_CantMove()
{
	if (playerREF)
	{
		playerREF->bSword1CanMove = true;
	}
}

void UPlayerAnimInstance::AnimNotify_IncreaseSpeed()
{
	if (playerREF)
	{
		playerREF->GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		playerREF->Anim_AtkEnd();
	}
}

void UPlayerAnimInstance::AnimNotify_InvisibleDash()
{
	if (playerREF)
	{
		playerREF->InvisibleDash();
	}
}

void UPlayerAnimInstance::AnimNotify_Footstep()
{
	UGameplayStatics::PlaySound2D(GetWorld(), footstepSound);
}
