// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerAnimInstance.h"

void UCustomerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	customer = Cast<ACustomer>(GetOwningActor());

}

void UCustomerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (customer)
	{
		currentState = customer->state;
		orderSuccess = customer->orderSuccess;
	}
}
