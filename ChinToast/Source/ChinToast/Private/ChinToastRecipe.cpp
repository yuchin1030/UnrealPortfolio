// Fill out your copyright notice in the Description page of Project Settings.


#include "ChinToastRecipe.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetArrayLibrary.h>

// Sets default values
AChinToastRecipe::AChinToastRecipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Bread(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Bread.Bread'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Cheese(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Cheese.Cheese'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BigHam(TEXT("/Script/Engine.StaticMesh'/Game/Yuchin/YC_Assets/Sandwich_Pieces/Need/Ham.Ham'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Hams(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Ham.Ham'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Lettuce(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Lettuce.Lettuce'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Tomato(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Tomato.Tomato'"));

	if (Bread.Succeeded())
	{
		ingredients.Add(TEXT("Bread"), Bread.Object);
	}
	if (Cheese.Succeeded())
	{
		ingredients.Add(TEXT("Cheese"), Cheese.Object);
	}
	if (BigHam.Succeeded())
	{
		ingredients.Add(TEXT("BigHam"), BigHam.Object);
	}
	if (Hams.Succeeded())
	{
		ingredients.Add(TEXT("Hams"), Hams.Object);
	}
	if (Lettuce.Succeeded())
	{
		ingredients.Add(TEXT("Lettuce"), Lettuce.Object);
	}
	if (Tomato.Succeeded())
	{
		ingredients.Add(TEXT("Tomato"), Tomato.Object);
	}

	ConstructorHelpers::FObjectFinder<UTexture2D> Breadimg(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Bread.Bread'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> Cheeseimg(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Cheese.Cheese'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> BigHamimg(TEXT("/Script/Engine.Texture2D'/Game/Yuchin/UI/BreadImg.BreadImg'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> Hamsimg(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Ham.Ham'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> Lettuceimg(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Lettuce.Lettuce'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> Tomatoimg(TEXT("/Script/Engine.Texture2D'/Game/BJK/UI/PNG/Menu/Tomato.Tomato'"));

	if (Breadimg.Succeeded())
	{
		foodimage.Add(TEXT("Bread Image"), Breadimg.Object);
	}
	if (Cheeseimg.Succeeded())
	{
		foodimage.Add(TEXT("Cheese Image"), Cheeseimg.Object);
	}
	if (BigHamimg.Succeeded())
	{
		foodimage.Add(TEXT("BigHam Image"), BigHamimg.Object);
	}
	if (Hamsimg.Succeeded())
	{
		foodimage.Add(TEXT("Hams Image"), Hamsimg.Object);
	}
	if (Lettuceimg.Succeeded())
	{
		foodimage.Add(TEXT("Lettuce Image"), Lettuceimg.Object);
	}
	if (Tomatoimg.Succeeded())
	{
		foodimage.Add(TEXT("Tomato Image"), Tomatoimg.Object);
	}

	recipe1 = { "Chin Toast", "Bread", "Hams", "Cheese", "Lettuce", "Bread"};
	recipe2 = { "Triple Ham Toast", "Bread", "Hams", "Hams", "Hams", "Bread" };
	recipe3 = { "Vegan Toast", "Bread", "Lettuce", "Tomato", "Lettuce", "Bread" };
	recipe4 = { "Double Cheese Toast", "Bread", "Hams", "Cheese", "Cheese", "Bread" };
	recipe5 = { "BLT Toast", "Bread", "Hams", "Tomato", "Lettuce", "Bread" };
	recipe6 = { "Min Toast", "Bread", "Bread", "Bread", "Bread", "Bread" };

}

// Called when the game starts or when spawned
void AChinToastRecipe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChinToastRecipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMesh* AChinToastRecipe::GetRecipe(FString metarialname)
{
	return ingredients[metarialname];
}

void AChinToastRecipe::SetRandomMenu()
{
	makedRecipe.Empty();
	int32 ramNum = FMath::RandRange(1, 5);
	UE_LOG(LogTemp, Warning, TEXT("%d"), ramNum);

	switch (ramNum)
	{
	case 1:
		for (int32 i = 0; i < recipe1.Num(); i++)
		{
			makedRecipe.Add(recipe1[i]);
		}
		break;
	case 2:
		for (int32 i = 0; i < recipe2.Num(); i++)
		{
			makedRecipe.Add(recipe2[i]);
		}
		break;
	case 3:
		for (int32 i = 0; i < recipe3.Num(); i++)
		{
			makedRecipe.Add(recipe3[i]);
		}
		break;
	case 4:
		for (int32 i = 0; i < recipe4.Num(); i++)
		{
			makedRecipe.Add(recipe4[i]);
		}
		break;
	case 5:
		for (int32 i = 0; i < recipe5.Num(); i++)
		{
			makedRecipe.Add(recipe5[i]);
		}
		break;
	default:
		break;
	}
}

