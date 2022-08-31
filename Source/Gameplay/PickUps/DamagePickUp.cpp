// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePickUp.h"

#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"


// Sets default values
ADamagePickUp::ADamagePickUp()
{

}

void ADamagePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* pPlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(!pPlayerCharacter)
	{
		return;
	}

	UCharacterWeaponComponent* pWeaponComponent = pPlayerCharacter->GetWeaponComponent();
	if(!IsValid(pWeaponComponent))
	{
		return;
	}

	pWeaponComponent->AddDamage(Value);

	Super::NotifyActorBeginOverlap(OtherActor);
}

