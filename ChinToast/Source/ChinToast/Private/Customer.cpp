

#include "Customer.h"
#include <ChinToastRecipe.h>
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	/*static ConstructorHelpers::FObjectFinder<UDataTable> FoodData(TEXT("/ Script / Engine.DataTable'/Game/KSW/DT_FoodData.DT_FoodData'"));
	if (FoodData.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Data Set"));
		foodData = FoodData.Object;
	}*/
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	
	RandomCustomerSet();

	startLoc = GetActorLocation();
	startRot = GetActorRotation();

	
	for (TActorIterator<AChinToastRecipe> toast(GetWorld()); toast; ++toast)
	{
		recipe = *toast;
	}


	if (recipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUUUUUU"));
	}

	/*auto list = foodData->GetRowNames();
	FName RamdomMenu = list[FMath::RandRange(0,4)];
	FFoodData* selectMenu = foodData->FindRow<FFoodData>(RamdomMenu,FString(""));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_menu);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_material1);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_material2);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_material3);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_material4);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *selectMenu->D_material5);*/
	
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ticktime += DeltaTime;

	switch (state)
	{
	case ECustomerState::IDLE:
		Idle();
		break;
	case ECustomerState::MOVEIN:
		MoveIn();
		break;
	case ECustomerState::WAITING:
		OrderWait();
		break;
	case ECustomerState::ORDER:
		Order();
		break;
	case ECustomerState::ORDERDELAY:
		Wait();
		break;
	case ECustomerState::CHECK:
		Check();
		break;
	case ECustomerState::PAYMENT:
		Payment();
		break;
	case ECustomerState::MOVEOUT:
		MoveOut();
		break;
	default:
		break;
	}
}

void ACustomer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomer::UpdateWaitingNum()
{
	waitingNum -= 1;
	state = ECustomerState::MOVEIN;
}

void ACustomer::RandomCustomerSet()
{
	ranNum = FMath::RandRange(0, 2);

	GetMesh()->SetSkeletalMesh(bodys[ranNum]);
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.2f));
	GetMesh()->SetAnimInstanceClass(customerMoves[ranNum]);
	//walkSpeed = 3.0f;
}

void ACustomer::Idle()
{
	if (ticktime > 1.0f)
	{
		ticktime = 0;
		state = ECustomerState::MOVEIN;
	}
}

void ACustomer::MoveIn()
{
	moveLoc = waitingLoc[waitingNum];
	
	if (FVector::Distance(GetActorLocation(), moveLoc) > 100.0f)
	{
		FVector moveDir = (moveLoc - GetActorLocation()).GetSafeNormal();
		SetActorLocation(GetActorLocation() + moveDir * walkSpeed, true);
		ticktime = 0;
	}
	else
	{
		FVector MoveSetLoc = FMath::Lerp(GetActorLocation(), moveLoc, 0.1);
		SetActorLocation(MoveSetLoc);
		if (waitingNum == 0)
		{
			FRotator MoveSetRot = FMath::Lerp(GetActorRotation(), moveRot, 0.1);
			SetActorRotation(MoveSetRot);
		}
		if (ticktime > 0.5f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Success: %d"), waitingNum);
			ticktime = 0;
			//UE_LOG(LogTemp,Warning,TEXT("Success"));
			if (waitingNum == 0)
			{
				state = ECustomerState::ORDER;
			}
			else
			{
				state = ECustomerState::WAITING;
			}
		}
	}
	
}

void ACustomer::OrderWait()
{
	FVector MoveSetLoc = FMath::Lerp(GetActorLocation(), moveLoc, 0.1);
	SetActorLocation(MoveSetLoc);
}

void ACustomer::Order()
{	
	ticktime = 0;
	recipe->SetRandomMenu();
	for (int32 i = 0; i < recipe->makedRecipe.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *recipe->makedRecipe[i]);
	}

	UE_LOG(LogTemp, Warning, TEXT("Order"));
	state = ECustomerState::ORDERDELAY;

}

void ACustomer::Wait()
{
	if (getfood || ticktime > 30.0f)
	{
		ticktime = 0;
		UE_LOG(LogTemp, Warning, TEXT("Time Over"));
		state = ECustomerState::CHECK;
	}
}

void ACustomer::Check()
{
	FRotator endSetRot = FMath::Lerp(GetActorRotation(), endRot, 0.1);
	SetActorRotation(endSetRot);
	if (ticktime > 1.0f)
	{
		ticktime = 0;
		if (orderSuccess)
		{
			UGameplayStatics::PlaySound2D(this, response[0]);
			PlayAnimMontage(thanks[ranNum]);
			state = ECustomerState::PAYMENT;
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, response[1]);
			state = ECustomerState::MOVEOUT;
		}
	}
}

void ACustomer::Payment()
{
	UE_LOG(LogTemp, Warning, TEXT("100$"));
	state = ECustomerState::MOVEOUT;
}

void ACustomer::MoveOut()
{
	if (FVector::Distance(GetActorLocation(), endLoc) > 100.0f)
	{
		FVector endDir = (endLoc - GetActorLocation()).GetSafeNormal();
		SetActorLocation(GetActorLocation() + endDir * walkSpeed, true);
		ticktime = 0;
	}
	else
	{
		SetActorLocation(startLoc);
		SetActorRotation(startRot);
		RandomCustomerSet();
		state = ECustomerState::IDLE;
		waitingNum = 2;
	}
	getfood = false;
	orderSuccess = false;

}

