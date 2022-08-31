// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeaponComponent.h"

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

#include "Tools/MacroTools.h"

void UCharacterWeaponComponent::SetWeaponType(EWeaponType Type)
{
	if (WeaponType == Type)
	{
		return;
	}

	auto* WeaponsSubsystem = UWeaponsSubsystem::Get(this);
	if (!EnsureMsg(IsValid(WeaponsSubsystem), TEXT("[CharacterWeaponComponent] Weapons Subsystem is not initialized")))
	{
		return;
	}

	const FWeaponData& WeaponData = WeaponsSubsystem->GetWeaponData(Type);
	if (!EnsureMsg(WeaponData.IsValid(), TEXT("[CharacterWeaponComponent] Weapon data is not valid")))
	{
		return;
	}

	WeaponType = Type;

	ParseWeaponData(WeaponData);

	OnWeaponChanged.Broadcast(WeaponType);
}

void UCharacterWeaponComponent::AddDamage(float Value)
{
	auto* Weapon = Cast<AWeapon>(GetChildActor());
	if (!Weapon)
	{
		return;
	}
	Weapon->AddDamage(Value);
}

void UCharacterWeaponComponent::ParseWeaponData(const FWeaponData& Data)
{
	if (!EnsureMsg(Data.IsValid(), TEXT("[CharacterWeaponComponent] Weapon data is not valid")))
	{
		return;
	}

	/* Creating weapon with specified type */
	SetChildActorClass(Data.WeaponClass);
	CreateChildActor();

	/* Parsing weapon data */
	SetRelativeTransform(Data.OverrideTransform);
	auto* Weapon = Cast<AWeapon>(GetChildActor());
	if (IsValid(Weapon))
	{
		Weapon->SetCooldown(Data.Cooldown);
		Weapon->SetDamage(Data.Damage);
		Weapon->SetDamageTypeClass(Data.DamageTypeClass);
	}
}

void UCharacterWeaponComponent::Fire(const ADefaultCharacter* Caller)
{
	auto* Weapon = Cast<AWeapon>(GetChildActor());
	if (IsValid(Weapon))
	{
		Weapon->Fire();
	}
}

void UCharacterWeaponComponent::ChangeWeapon(const EChangeDirection ChangeDirection)
{
	if (Weapons.Num() <= 0)
	{
		return;
	}
	int32 Index = 0;
	Weapons.Find(WeaponType, Index);
	switch (ChangeDirection)
	{
	case EChangeDirection::Next:
		Index++;
		break;
	case EChangeDirection::Previous:
		Index--;
		break;
	default:
		return;
	}
	if (Weapons.IsValidIndex(Index))
	{
		SetWeaponType(Weapons[Index]);
	}
	else
	{
		SetWeaponType(Weapons[Modulo(Index, Weapons.Num())]);
	}
}

int32 UCharacterWeaponComponent::Modulo(int32 Dividend, int32 Divisor) const
{
	return (Divisor + Dividend % Divisor) % Divisor;
}
