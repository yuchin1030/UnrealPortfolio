

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



	// VRī�޶� ������Ʈ�� ����.
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UCameraComponent* cameraComp;


	// �޼�, ������ ��Ʈ�ѷ� ������Ʈ ����
	// �޼� ��� ��Ʈ�ѷ� ������Ʈ ����
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UMotionControllerComponent* motionLeft;

	// ������ ��� ��Ʈ�ѷ� ������Ʈ ����
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UMotionControllerComponent* motionRight;



	// �޼�, ������ ���̷�Ż �޽� ������Ʈ�� ���� ��� ��Ʈ�ѷ��� ���̰�ʹ�.
	// �޼� �Ž� ������Ʈ �߰�
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USkeletalMeshComponent* meshLeft;

	// ������ �Ž� ������Ʈ �߰�
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USkeletalMeshComponent* meshRight;




	// �޼�, ������ ���̷�Ż �޽� �ε��ؼ� �����ϰ�ʹ�.
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
