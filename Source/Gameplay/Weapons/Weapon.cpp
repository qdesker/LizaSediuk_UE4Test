// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (IsValid(Mesh))
	{
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}
}

bool AWeapon::Fire()
{
	if (!CanFire())
	{
		return false;
	}

	CurrentCooldown = Cooldown;
	bIsCooledDown = false;

	return true;
}

bool AWeapon::CanFire() const
{
	return bIsCooledDown;
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentCooldown -= DeltaTime;
	bIsCooledDown = CurrentCooldown <= 0.0f;
}

