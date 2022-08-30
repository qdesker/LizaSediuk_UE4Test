// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "DefaultCharacter.generated.h"

class UCharacterWeaponComponent;
class UCharacterInputArbiterComponent;
class UCharacterHealthComponent;
class AWeapon;

UCLASS(config=Game)
class ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ADefaultCharacter();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime) override;

	bool IsEnemy(AActor* Actor) const;
	bool IsDead() const;

	virtual void OnDamageReceived(const ADefaultCharacter* FromCharacter, const AWeapon* WithWeapon, const FHitResult& Hit);

protected:

	virtual void BeginPlay() override;

	/* Firing, Weapons */

	void Fire();

	UPROPERTY(EditAnywhere, Category = "Weapons")
	EWeaponType DefaultWeaponType = EWeaponType::AK47;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UCharacterWeaponComponent* CurrentWeapon;

	/* Inputs */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	UCharacterInputArbiterComponent* InputArbiter;

	/* Health */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UCharacterHealthComponent* Health;

	/* Death */

	UFUNCTION()
	virtual void OnDead();

private:

	/* Enemies */

	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<UClass*> EnemiesList;

	UPROPERTY(EditAnywhere)
	float DelayBeforeRemovingAfterDeath = 10.0f;

	FTimerHandle DeathHandle;
};

