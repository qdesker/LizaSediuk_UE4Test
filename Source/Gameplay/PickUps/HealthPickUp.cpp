// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"

#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Components/Common/CharacterHealthComponent.h"


// Sets default values
AHealthPickUp::AHealthPickUp()
{

}

void AHealthPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* pPlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(!pPlayerCharacter)
	{
		return;
	}

	UCharacterHealthComponent* pHealthComponent = pPlayerCharacter->GetHealthComponent();
	if(!IsValid(pHealthComponent))
	{
		return;
	}

	pHealthComponent->AddHealth(Value);

	Super::NotifyActorBeginOverlap(OtherActor);
}


