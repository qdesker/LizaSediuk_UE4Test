// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputArbiterComponent.h"

#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Components/Player/PlayerCameraComponent.h"

#include "Tools/MacroTools.h"

void UPlayerInputArbiterComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	/* Set up gameplay key bindings */

	if (!EnsureMsg(IsValid(PlayerInputComponent), TEXT("[PlayerInputArbiter] No PlayerInputComponent, logic is broken")))
	{
		return;
	}

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerInputArbiterComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &UPlayerInputArbiterComponent::StopFire);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &UPlayerInputArbiterComponent::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &UPlayerInputArbiterComponent::StopCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &UPlayerInputArbiterComponent::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &UPlayerInputArbiterComponent::StopJump);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &UPlayerInputArbiterComponent::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &UPlayerInputArbiterComponent::StopAim);

	PlayerInputComponent->BindAxis("MoveForward", this, &UPlayerInputArbiterComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &UPlayerInputArbiterComponent::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &UPlayerInputArbiterComponent::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &UPlayerInputArbiterComponent::LookUp);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &UPlayerInputArbiterComponent::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &UPlayerInputArbiterComponent::PreviousWeapon);
}

void UPlayerInputArbiterComponent::StartAim()
{
	Super::StartAim();

	auto* Character = Cast<APlayerCharacter>(GetOwner());
	if (!EnsureMsg(IsValid(Character), TEXT("[PlayerInputArbiter] Owner is not player character which is wrong")))
	{
		return;
	}

	UPlayerCameraComponent* FollowCamera = Character->GetFollowCamera();
	if (!EnsureMsg(IsValid(FollowCamera), TEXT("[PlayerInputArbiter] No FollowCamera in player character")))
	{
		return;
	}

	FollowCamera->StartAiming();
}

void UPlayerInputArbiterComponent::StopAim()
{
	Super::StopAim();

	auto* Character = Cast<APlayerCharacter>(GetOwner());
	if (!EnsureMsg(IsValid(Character), TEXT("[PlayerInputArbiter] Owner is not player character which is wrong")))
	{
		return;
	}

	UPlayerCameraComponent* FollowCamera = Character->GetFollowCamera();
	if (!EnsureMsg(IsValid(FollowCamera), TEXT("[PlayerInputArbiter] No FollowCamera in player character")))
	{
		return;
	}

	FollowCamera->StopAiming();
}
