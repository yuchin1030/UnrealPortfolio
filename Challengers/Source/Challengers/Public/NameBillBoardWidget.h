// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NameBillBoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UNameBillBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* name;

};
