

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h>
#include "VRPlayer.generated.h"

UCLASS()
class CHINTOAST_API AVRPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	AVRPlayer();

protected:
	
	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// VR카메라 컴포넌트를 생성.
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UCameraComponent* cameraComp;


	// 왼손, 오른손 컨트롤러 컴포넌트 생성
	// 왼손 모션 컨트롤러 컴포넌트 생성
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UMotionControllerComponent* motionLeft;

	// 오른손 모션 컨트롤러 컴포넌트 생성
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UMotionControllerComponent* motionRight;



	// 왼손, 오른손 스켈레탈 메시 컴포넌트를 만들어서 모션 컨트롤러에 붙이고싶다.
	// 왼손 매쉬 컴포넌트 추가
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USkeletalMeshComponent* meshLeft;

	// 오른손 매쉬 컴포넌트 추가
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USkeletalMeshComponent* meshRight;




	// 왼손, 오른손 스켈레탈 메시 로드해서 적용하고싶다.
	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UInputMappingContext* IMC_VRPlayer;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UInputAction* IA_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UInputAction* IA_Grab_Left;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
	class UInputAction* IA_Grab_Right;


	void OnIAMove(const FInputActionValue& value);
	void OnIATurn(const FInputActionValue& value);
	void OnIAGrab_Left(const FInputActionValue& value);
	void OnIAGrab_Right(const FInputActionValue& value);



};
