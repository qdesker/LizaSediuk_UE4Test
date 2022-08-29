// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeaponSFXComponent.h"

#include "Tools/MacroTools.h"
#include "Tools/GameplayToolbox.h"

void URifleWeaponSFXComponent::PlayFireSound()
{
	if (!EnsureMsg(IsValid(SFXData.SingleShotSound.Sound), TEXT("[RifleWeaponSFXComponent] SingleShotSound is not set")))
	{
		return;
	}

	if (!IsValid(GetOwner()))
	{
		return;
	}

	UGameplayToolbox::PlaySoundAtLocation(this, GetOwner()->GetActorLocation(), SFXData.SingleShotSound);
}

void URifleWeaponSFXComponent::PlayBulletHitSound(const FHitResult& Hit)
{
	const AActor* TargetActor = Hit.Actor.Get();
	if (!EnsureMsg(IsValid(TargetActor), TEXT("[RifleWeaponSFXComponent] Actor in HitResult is not valid")))
	{
		return;
	}

	const FSimpleSFXData& TargetFXData = GetBulletHitSFXDataForActor(TargetActor);
	if (!EnsureMsg(IsValid(TargetFXData.Sound), TEXT("[RifleWeaponSFXComponent] Sound is not set")))
	{
		return;
	}

	UGameplayToolbox::PlaySoundAtLocation(this, Hit.Location, TargetFXData);
}

const FSimpleSFXData& URifleWeaponSFXComponent::GetBulletHitSFXDataForActor(const AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return SFXData.BulletHitSoundDefault;
	}

	for (auto&& BulletHitSFX : SFXData.BulletHitSounds)
	{
		if (Actor->IsA(BulletHitSFX.Key))
		{
			return BulletHitSFX.Value;
		}
	}

	/* Use default FX If certain is not set */
	return SFXData.BulletHitSoundDefault;
}
