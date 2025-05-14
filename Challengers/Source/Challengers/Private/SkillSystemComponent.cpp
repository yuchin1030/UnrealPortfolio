// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystemComponent.h"
#include "../../../Source/Runtime/Engine/Classes/Kismet/DataTableFunctionLibrary.h"
#include "TestPreset.h"

USkillSystemComponent::USkillSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USkillSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	SwordSkillArr.Init(false, SwordSkillCnt);	// {false, false, false}
	WandSkillArr.Init(false, WandSkillCnt);
	GunSkillArr.Init(false, GunSkillCnt);
}


void USkillSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
