// Fill out your copyright notice in the Description page of Project Settings.


#include "Toolbox.h"

#include "Controllers/DefaultPlayerController.h"

#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/GameModes/DefaultGameMode.h"

ADefaultPlayerController* UToolbox::GetCurrentPlayerController(const UObject* WorldContextObject)
{
	UGameInstance* GInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (IsValid(GInstance))
	{
		return Cast<ADefaultPlayerController>(GInstance->GetFirstLocalPlayerController());
	}

	return nullptr;
}

APlayerCharacter* UToolbox::GetCurrentPlayerCharacter(const UObject* WorldContextObject)
{
	ADefaultPlayerController* PlayerController = GetCurrentPlayerController(WorldContextObject);
	if (IsValid(PlayerController))
	{
		return PlayerController->GetPawn<APlayerCharacter>();
	}

	return nullptr;
}

APlayerCameraManager* UToolbox::GetCurrentPlayerCameraManager(const UObject* WorldContextObject)
{
	ADefaultPlayerController* PlayerController = GetCurrentPlayerController(WorldContextObject);
	if (IsValid(PlayerController))
	{
		return PlayerController->PlayerCameraManager;
	}

	return nullptr;
}

FRotator UToolbox::GetPlayerCameraRotation(const UObject* WorldContextObject)
{
	const APlayerCameraManager* CameraMgr = GetCurrentPlayerCameraManager(WorldContextObject);
	if (IsValid(CameraMgr))
	{
		return CameraMgr->GetCameraRotation();
	}

	return FRotator::ZeroRotator;
}

bool UToolbox::IsGameOver(const UObject* WorldContextObject)
{
	auto* CurrentGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (IsValid(CurrentGameMode))
	{
		return CurrentGameMode->IsGameOver();
	}

	return false;
}

bool UToolbox::IsCurrentPlayerDead(const UObject* WorldContextObject)
{
	const APlayerCharacter* PlayerCharacter = UToolbox::GetCurrentPlayerCharacter(WorldContextObject);
	if (IsValid(PlayerCharacter))
	{
		return PlayerCharacter->IsDead();
	}

	return false;
}
