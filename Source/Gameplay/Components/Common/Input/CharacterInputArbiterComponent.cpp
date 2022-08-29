// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInputArbiterComponent.h"

#include "Gameplay/Characters/DefaultCharacter.h"

#include "Tools/MacroTools.h"

UCharacterInputArbiterComponent::UCharacterInputArbiterComponent()
	: Super::UActorComponent()
{

}

void UCharacterInputArbiterComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ADefaultCharacter>(GetOwner());
	EnsureMsg(IsValid(OwnerCharacter), TEXT("[InputArbiter] Owner is not character which is wrong"));
}

void UCharacterInputArbiterComponent::StartFire()
{
	bIsFiring = true;
}

void UCharacterInputArbiterComponent::StopFire()
{
	bIsFiring = false;
}

void UCharacterInputArbiterComponent::StartCrouch()
{
	bIsCrouching = true;
}

void UCharacterInputArbiterComponent::StopCrouch()
{
	bIsCrouching = false;
}

void UCharacterInputArbiterComponent::StartJump()
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	bIsJumping = OwnerCharacter->CanJump();

	OwnerCharacter->Jump();
}

void UCharacterInputArbiterComponent::StopJump()
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	bIsJumping = false;

	OwnerCharacter->StopJumping();
}

void UCharacterInputArbiterComponent::StartAim()
{
	bIsAiming = true;
}

void UCharacterInputArbiterComponent::StopAim()
{
	bIsAiming = false;
}

void UCharacterInputArbiterComponent::MoveForward(float Value)
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	if (Value != 0.0f)
	{
		const FRotator Rotation = OwnerCharacter->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		OwnerCharacter->AddMovementInput(Direction, Value);
	}
}

void UCharacterInputArbiterComponent::MoveRight(float Value)
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	if (Value != 0.0f)
	{
		const FRotator Rotation = OwnerCharacter->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		OwnerCharacter->AddMovementInput(Direction, Value);
	}
}

void UCharacterInputArbiterComponent::Turn(float Value)
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	OwnerCharacter->AddControllerYawInput(Value);
}

void UCharacterInputArbiterComponent::LookUp(float Value)
{
	if (!EnsureMsg(IsValid(OwnerCharacter), TEXT("OwnerCharacter is invalid")))
	{
		return;
	}

	OwnerCharacter->AddControllerPitchInput(Value);
}
