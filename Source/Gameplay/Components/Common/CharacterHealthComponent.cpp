// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHealthComponent.h"

#include "DataHolders/Gameplay/DamageData/DamageDataAsset.h"

#include "Tools/MacroTools.h"

void UCharacterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = InitialHealth;
}

void UCharacterHealthComponent::OnDamageReceived(float Damage, const FName& HitInBone)
{
	if (IsDead())
	{
		/* Ignore any damage if the character is already dead */
		return;
	}

	if (!EnsureMsg(IsValid(DamageDatabase), TEXT("[ChracterHealthComponent] Cannot receive damage, DamageDatabase wasn't selected")))
	{
		return;
	}

	CurrentHealth -= Damage * DamageDatabase->GetBoneDamageMultiplier(HitInBone);
	OnHealthChanged.Broadcast();

	if (IsDead())
	{
		OnDead();
	}
}

void UCharacterHealthComponent::OnDead()
{
	OnDeadDelegate.Broadcast();
}


