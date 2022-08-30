// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDHealthBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Tools/Toolbox.h"
#include "Gameplay/Components/Common/CharacterHealthComponent.h"

void UInGameHUDHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	const UWorld* pWorld = GetWorld();
	if (!pWorld)
	{
		return;
	}

	const APlayerCharacter* pPlayer = UToolbox::GetCurrentPlayerCharacter(pWorld);
	if (!pPlayer)
	{
		return;
	}

	auto* pHealthComponent = Cast<UCharacterHealthComponent>(pPlayer->GetComponentByClass(UCharacterHealthComponent::StaticClass()));
	if(!IsValid(pHealthComponent))
	{
		return;
	}
	HealthComponentWeakPtr = TWeakObjectPtr<UCharacterHealthComponent>(pHealthComponent);

	pHealthComponent->OnHealthChanged.AddDynamic(this, &UInGameHUDHealthBar::OnHealthChanged);

	ChangeState(pHealthComponent->GetInitialHealthValue(), pHealthComponent->GetInitialHealthValue());
}

void UInGameHUDHealthBar::NativeDestruct()
{
	if(!HealthComponentWeakPtr.IsValid())
	{
		return;
	}
	HealthComponentWeakPtr.Get()->OnHealthChanged.RemoveAll(this);
	Super::NativeDestruct();
}

void UInGameHUDHealthBar::OnHealthChanged()
{
	if (!HealthComponentWeakPtr.IsValid())
	{
		return;
	}

	const UCharacterHealthComponent* pHealthComponent = HealthComponentWeakPtr.Get();

	ChangeState(pHealthComponent->GetCurrentHealthValue(), pHealthComponent->GetInitialHealthValue());

}

void UInGameHUDHealthBar::ChangeState(float CurrentHealth, float InitialHealth)
{
	Health->SetPercent(CurrentHealth / InitialHealth);

	HealthValue->SetText(FText::FromString(FString::FromInt(CurrentHealth) + "/" + FString::FromInt(InitialHealth)));
}
