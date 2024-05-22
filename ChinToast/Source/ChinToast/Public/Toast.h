
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Toast.generated.h"

UCLASS()
class CHINTOAST_API AToast : public AActor
{
	GENERATED_BODY()
	
public:	
	AToast();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	class UBoxComponent* makingArea;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	class UBoxComponent* pickUpArea;

	UPROPERTY()
	TArray<UStaticMesh*> inside;

	UPROPERTY()
	class AChinToastRecipe* recipe;

};
