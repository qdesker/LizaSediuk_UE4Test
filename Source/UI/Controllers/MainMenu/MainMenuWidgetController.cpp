// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetController.h"

#include "UI/Widgets/MainMenu/MainMenuWidget.h"
#include "Subsystems/Persistent/LevelsSubsystem.h"

#include "Tools/MacroTools.h"

bool UMainMenuWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	if (!Super::Initialize(_Widget))
	{
		return false;
	}

	MainMenuWidget = Cast<UMainMenuWidget>(_Widget);
	if (!EnsureMsg(IsValid(MainMenuWidget), TEXT("[MainMenuWidgetController] No Widget set")))
	{
		return false;
	}

	MainMenuWidget->OnPlayClicked.AddUObject(this, &UMainMenuWidgetController::OnPlayClicked);

	return true;
}

void UMainMenuWidgetController::BeginDestroy()
{
	if (IsValid(MainMenuWidget))
	{
		MainMenuWidget->OnPlayClicked.RemoveAll(this);
	}

	Super::BeginDestroy();
}

void UMainMenuWidgetController::OnPlayClicked()
{
	auto* LevelsSubsystem = ULevelsSubsystem::Get(this);
	if (IsValid(LevelsSubsystem))
	{
		LevelsSubsystem->LoadLevel(EAvailableLevels::DefendTheCastle_ElvenRuins);
	}
}
