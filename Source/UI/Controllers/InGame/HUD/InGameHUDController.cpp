// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDController.h"

#include <Kismet/GameplayStatics.h>

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

#include "Gameplay/GameModes/CastleDefenderGameMode.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"

#include "UI/Widgets/InGame/HUD/InGameHUDWidget.h"

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

bool UInGameHUDController::Initialize(UDefaultUserWidget* _Widget)
{
	if (!Super::Initialize(_Widget))
	{
		return false;
	}

	InGameHUDWidget = Cast<UInGameHUDWidget>(_Widget);
	if (!EnsureMsg(IsValid(InGameHUDWidget), TEXT("InGameHUDWidget has incorrect type")))
	{
		return false;
	}

	SetTickEnabled(true);

	UpdateMissionInfo();
	SubscribeOnWeaponChanged();

	return true;
}

void UInGameHUDController::BeginDestroy()
{
	UnsubscribeOnWeaponChanged();

	Super::BeginDestroy();
}

bool UInGameHUDController::TickController(float DeltaTime)
{
	if (!Super::TickController(DeltaTime))
	{
		return false;
	}

	auto* CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this));
	if (IsValid(CurrentGameMode))
	{
		SetTimerValue(CurrentGameMode->GetRemainingDefenceTime());
	}

	return true;
}

void UInGameHUDController::SetTimerValue(float ValueInSeconds)
{
	if (!EnsureMsg(IsValid(InGameHUDWidget), TEXT("InGameHUDWidget is invalid")))
	{
		return;
	}

	InGameHUDWidget->SetDefenceTimerValue(ValueInSeconds);
}

void UInGameHUDController::UpdateMissionInfo()
{
	if (!EnsureMsg(IsValid(InGameHUDWidget), TEXT("InGameHUDWidget is invalid")))
	{
		return;
	}

	auto* CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this));
	if (!EnsureMsg(IsValid(CurrentGameMode), TEXT("CurrentGameMode is invalid")))
	{
		return;
	}

	FString MissionDescr = CurrentGameMode->GetMissionDescription();
	FString Time = FString::FromInt(static_cast<int32>(CurrentGameMode->GetDefenceTime()));
	FString TimeUnits = CurrentGameMode->GetTimeUnits();

	InGameHUDWidget->SetMissionInfo(MissionDescr + Time + TimeUnits);
}

void UInGameHUDController::UpdateCurrentWeaponInfo(EWeaponType Type)
{
	if (!EnsureMsg(IsValid(InGameHUDWidget), TEXT("InGameHUDWidget is invalid")))
	{
		return;
	}

	auto* WeaponsSubsystem = UWeaponsSubsystem::Get(this);
	if (!EnsureMsg(IsValid(WeaponsSubsystem), TEXT("[InGameHUDController] Cannot get WeaponsSubsystem")))
	{
		return;
	}

	const FWeaponData& WeaponData = WeaponsSubsystem->GetWeaponData(Type);
	if (!EnsureMsg(WeaponData.IsValid(), TEXT("WeaponData is invalid")))
	{
		return;
	}

	InGameHUDWidget->SetCurrentWeaponName(WeaponData.DisplayName);
}

void UInGameHUDController::SubscribeOnWeaponChanged()
{
	const APlayerCharacter* CurrentPlayer = UToolbox::GetCurrentPlayerCharacter(this);
	if (!EnsureMsg(IsValid(CurrentPlayer), TEXT("[InGameHUDController] Cannot find player's character")))
	{
		return;
	}

	auto* WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentPlayer->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));
	if (!EnsureMsg(IsValid(WeaponComponent), TEXT("[InGameHUDController] Cannot find WeaponComponent")))
	{
		return;
	}

	WeaponComponent->OnWeaponChanged.AddUObject(this, &UInGameHUDController::UpdateCurrentWeaponInfo);
}

void UInGameHUDController::UnsubscribeOnWeaponChanged()
{
	const APlayerCharacter* CurrentPlayer = UToolbox::GetCurrentPlayerCharacter(this);
	if (!IsValid(CurrentPlayer))
	{
		return;
	}

	auto* WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentPlayer->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));
	if (!IsValid(WeaponComponent))
	{
		return;
	}

	WeaponComponent->OnWeaponChanged.RemoveAll(this);
}

