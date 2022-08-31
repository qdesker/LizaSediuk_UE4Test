// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "CharacterWeaponComponent.generated.h"

class ADefaultCharacter;

UENUM()
enum class EChangeDirection
{
	None = 0,

	Next,

	Previous
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedDelegate, EWeaponType);

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UCharacterWeaponComponent : public UChildActorComponent
{
	GENERATED_BODY()
	
public:

	virtual void SetWeaponType(EWeaponType Type);

	EWeaponType GetWeaponType() const { return WeaponType; }

	virtual void Fire(const ADefaultCharacter* Caller);

	virtual void ChangeWeapon(const EChangeDirection ChangeDirection);

	FOnWeaponChangedDelegate OnWeaponChanged;

protected:

	virtual void ParseWeaponData(const FWeaponData& Data);

private:

	/**
	 * We need this function because the "%" definition in c++ is not the same as in math. In math the remainder
	 * cannot be negative, which c++ is accept.
	*/
	int32 Modulo(int32 Dividend, int32 Divisor) const;

	UPROPERTY(EditAnywhere)
	TArray<EWeaponType> Weapons;

	EWeaponType WeaponType = EWeaponType::None;
};
