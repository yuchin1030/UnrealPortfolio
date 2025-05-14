// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "DungeonEditCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ADungeonEditCharacter : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:
	ADungeonEditCharacter();

	// ���� ������ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UDungeonEditComponent* dungeonEditComponent;

};
