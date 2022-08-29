// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefaultCharacter.h"

#include "Gameplay/Weapons/Rifles/RifleWeapon.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "Gameplay/Components/Common/Input/CharacterInputArbiterComponent.h"
#include "Gameplay/Components/Common/ChracterHealthComponent.h"
#include "Gameplay/GameModes/DefaultGameMode.h"

#include <Kismet/GameplayStatics.h>
#include <TimerManager.h>

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

ADefaultCharacter::ADefaultCharacter()
	: Super::ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Health */
	Health = CreateDefaultSubobject<UChracterHealthComponent>(TEXT("Health"));
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InputArbiter && InputArbiter->IsFiring()
		&& CanJump()
		&& !UToolbox::IsGameOver(this))
	{
		Fire();
	}
}

void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (EnsureMsg(IsValid(CurrentWeapon), TEXT("[DefaultCharacter] CurrentWeapon is not set in derived class constructor")))
	{
		CurrentWeapon->SetWeaponType(DefaultWeaponType);
	}

	if (EnsureMsg(IsValid(Health), TEXT("[DefaultCharacter] Health is invalid")))
	{
		Health->OnDeadDelegate.AddDynamic(this, &ADefaultCharacter::OnDead);
	}
}

void ADefaultCharacter::BeginDestroy()
{
	if (IsValid(Health))
	{
		Health->OnDeadDelegate.RemoveAll(this);
	}

	Super::BeginDestroy();
}

bool ADefaultCharacter::IsEnemy(AActor* Actor) const
{
	if (!EnsureMsg(Actor, TEXT("[DefaultCharacter] Cannot check on IsEnemy, the actor is nullptr")))
	{
		return false;
	}

	for (const UClass* EnemyClass : EnemiesList)
	{
		if (Actor->IsA(EnemyClass))
		{
			return true;
		}
	}

	return false;
}

bool ADefaultCharacter::IsDead() const
{
	if (!IsValid(Health))
	{
		return false;
	}

	return Health->IsDead();
}

void ADefaultCharacter::OnDamageReceived(const ADefaultCharacter* FromCharacter, const AWeapon* WithWeapon, const FHitResult& Hit)
{
	/* If a certain bone was hit, we take it into account */
	FName BoneHit = NAME_None;

	const USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	if (IsValid(SkeletalMeshComp))
	{
		FClosestPointOnPhysicsAsset ClosestPoint;
		SkeletalMeshComp->GetClosestPointOnPhysicsAsset(Hit.Location, ClosestPoint, true);
		BoneHit = ClosestPoint.BoneName;
	}

	if (!IsValid(Health))
	{
		return;
	}

	Health->OnDamageReceived(WithWeapon->GetDamage(), BoneHit);
}

void ADefaultCharacter::Fire()
{
	if (EnsureMsg(CurrentWeapon, TEXT("[DefaultCharacter] CurrentWeapon is not set in derived class constructor")))
	{
		CurrentWeapon->Fire(this);
	}
}

void ADefaultCharacter::OnDead()
{
	if (!IsValid(CurrentWeapon) || !IsValid(InputArbiter) || !IsValid(GetWorld()))
	{
		return;
	}

	DisableInput(Cast<APlayerController>(GetController()));
	CurrentWeapon->Deactivate();
	InputArbiter->Deactivate();

	if (DelayBeforeRemovingAfterDeath > 0.0f)
	{
		/* If character is dead -> remove it from the world */
		GetWorld()->GetTimerManager().SetTimer(DeathHandle,
			FTimerDelegate::CreateWeakLambda(this, [this]
			{
				delete this;
			}), DelayBeforeRemovingAfterDeath, false);
	}
}
