
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Customer.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	IDLE		UMETA(DisplayName = "Idle State"),
	MOVEIN		UMETA(DisplayName = "Move In State"),
	WAITING		UMETA(DisplayName = "OrderWait State"),
	ORDER		UMETA(DisplayName = "Order State"),
	ORDERDELAY	UMETA(DisplayName = "Order Delay State"),
	CHECK		UMETA(DisplayName = "Check State"),
	PAYMENT		UMETA(DisplayName = "Pay State"),
	MOVEOUT		UMETA(DisplayName = "Move Out State"),
};
UCLASS()
class CHINTOAST_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 고객 종류에 따라 바뀔 메쉬 저장용
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TArray <USkeletalMesh*> bodys;

	// 고객 종류에 따라 바뀔 ABP 저장용
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TArray <UClass*> customerMoves;

	// 손에 들고갈 샌드위치 매쉬
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	class UStaticMeshComponent* sandwich;

	// 수령확인 후 인사 애니몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TArray <UAnimMontage*> thanks;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TArray <USoundBase*> response;

	// FSM 상태변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting")
	ECustomerState state = ECustomerState::IDLE;

	// 주문할 샌드위치 레시피 재료 순서
	class AChinToastRecipe* recipe;

	UPROPERTY(EditAnywhere, Category = "Setting")
	TArray<FString> currentrecipe;

	// 고객 종류(매쉬 타입)
	UPROPERTY(EditAnywhere, Category = "Setting")
	int32 customerType = 0;

	// 이동용 좌표
	UPROPERTY(EditAnywhere, Category = "Setting")
	FVector moveLoc = FVector::ZeroVector;

	// 회전 경로
	UPROPERTY(EditAnywhere, Category = "Setting")
	FRotator moveRot = FRotator::ZeroRotator;

	// 나가는 경로
	UPROPERTY(EditAnywhere, Category = "Setting")
	FVector endLoc = FVector::ZeroVector;

	// 회전 경로
	UPROPERTY(EditAnywhere, Category = "Setting")
	FRotator endRot = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	bool orderSuccess = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString material1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString material2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString material3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString material4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString material5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UDataTable* foodData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool getfood = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 waitingNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FVector> waitingLoc;

	UFUNCTION(BlueprintCallable)
	void UpdateWaitingNum();
private:

	int32 ranNum;
	FVector startLoc;
	FRotator startRot;
	float ticktime = 0.0f;
	float walkSpeed = 3.0f;
	
	void RandomCustomerSet();

	void Idle();
	void MoveIn();
	void OrderWait();
	void Order();
	void Wait();
	void Check();
	void Payment();
	void MoveOut();
};
