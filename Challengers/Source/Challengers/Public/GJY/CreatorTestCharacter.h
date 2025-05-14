#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatorTestCharacter.generated.h"

UCLASS()
class CHALLENGERS_API ACreatorTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACreatorTestCharacter();

protected:
	virtual void BeginPlay() override;


public:	



	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	TSubclassOf<UUserWidget> CustomUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MeshBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// 캐릭터 스켈레탈 메시 부위별로 생성
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part1;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part2;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part3;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part4;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part5;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part6;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part7;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part8;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part9;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part10;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part11;


	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part12;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part13;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part14;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part15;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part16;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part17;


	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class UClass* ABP_MaleCustom;
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class UClass* ABP_FemaleCustom;


	int32 HairIndex = 0;
	int32 ClothesIndex = 0;
	int32 GlovesIndex = 0;
	
	UPROPERTY()
	UDataTable* BodyDataTable;
	UPROPERTY()
	UDataTable* HDT;
	UPROPERTY()
	UDataTable* CDT;
	UPROPERTY()
	UDataTable* SDT;

	UPROPERTY()
	TArray<FName> FinalMeshArr;

	UPROPERTY()
	TArray<FName> MaleMeshArr;

	UPROPERTY()
	TArray<FName> FemaleMeshArr;

	bool bBoy = true;
	bool bGlove = false;

	int GloveNum = 0;
	int ClothesNum = 0;
	int HairNum = 0;

	class UPlayerCustomizer* Customs;


	UFUNCTION()
	void ChangeHair();
	UFUNCTION()
	void ChangeClothes();
	UFUNCTION()
	void ChangeGloves();

	UFUNCTION()
	void HairColorChange(int _RowNum);
	UFUNCTION()
	void ClothesColorChange(int _RowNum);

	UFUNCTION()
	void SelectBoy();

	UFUNCTION()
	void SelectGirl();

	UFUNCTION()
	void LoadArray();

	UFUNCTION()
	void ChangeAnim();

	UFUNCTION()
	void InitColor();
};
