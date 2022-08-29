// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverController.h"

#include "UI/Widgets/InGame/Other/GameOverWidget.h"
#include "Gameplay/GameModes/CastleDefenderGameMode.h"
#include "Controllers/DefaultPlayerController.h"
#include "Subsystems/Persistent/LevelsSubsystem.h"

#include <Kismet/GameplayStatics.h>

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

bool UGameOverController::Initialize(UDefaultUserWidget* _Widget)
{
	if (!Super::Initialize(_Widget))
	{
		return false;
	}

	GameOverWidget = Cast<UGameOverWidget>(Widget);
	if (!EnsureMsg(IsValid(GameOverWidget), TEXT("GameOverWidget has incorrect type")))
	{
		return false;
	}

	GameOverWidget->OnBackButtonPressed.AddUObject(this, &UGameOverController::OnBackToMenuPressed);

	auto* CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this));
	if (!EnsureMsg(IsValid(CurrentGameMode), TEXT("CurrentGameMode is invalid")))
	{
		return false;
	}

	CurrentGameMode->OnGameOverDelegate.AddUObject(this, &UGameOverController::OnGameOver);

	return true;
}

void UGameOverController::BeginDestroy()
{
	if (IsValid(GameOverWidget))
	{
		GameOverWidget->OnBackButtonPressed.RemoveAll(this);
	}

	auto* CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this));
	if (IsValid(CurrentGameMode))
	{
		CurrentGameMode->OnGameOverDelegate.RemoveAll(this);
	}

	Super::BeginDestroy();
}

void UGameOverController::OnGameOver(EDefenceGameModeResult Result)
{
	ADefaultPlayerController* CurrentController = UToolbox::GetCurrentPlayerController(this);
	if (!EnsureMsg(IsValid(CurrentController), TEXT("[GameOverController] CurrentController is missing")))
	{
		return;
	}

	CurrentController->SetInputMode(FInputModeUIOnly());
	CurrentController->bShowMouseCursor = true;

	if (!IsValid(GameOverWidget))
	{
		return;
	}

	GameOverWidget->SetVisibility(ESlateVisibility::Visible);
	GameOverWidget->SetVictoryResult(Result);
}

void UGameOverController::OnBackToMenuPressed()
{
	auto* LevelsSubsystem = ULevelsSubsystem::Get(this);
	if (IsValid(LevelsSubsystem))
	{
		LevelsSubsystem->LoadLevel(EAvailableLevels::MainMenu_ElvenRuins);
	}
}
