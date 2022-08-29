// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidgetController.h"

#include "UI/Widgets/InGame/InGameWidget.h"
#include "UI/Widgets/InGame/HUD/InGameHUDWidget.h"
#include "UI/Widgets/InGame/Other/GameOverWidget.h"
#include "UI/Controllers/InGame/HUD/InGameHUDController.h"
#include "UI/Controllers/InGame/Other/GameOverController.h"

#include "Tools/MacroTools.h"

bool UInGameWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	if (!Super::Initialize(_Widget))
	{
		return false;
	}

	auto* InGameWidget = Cast<UInGameWidget>(_Widget);
	if (!EnsureMsg(IsValid(InGameWidget), TEXT("InGameWidget has incorrect type")))
	{
		return false;
	}

	if (!EnsureMsg(HUDControllerClass, TEXT("HUDControllerClass wasn't set")))
	{
		return false;
	}

	HUDController = NewObject<UInGameHUDController>(this, HUDControllerClass);
	if (EnsureMsg(IsValid(HUDController), TEXT("HUDController cannot be created")))
	{
		HUDController->Initialize(InGameWidget->GetInGameHUDWidget());
	}

	if (!EnsureMsg(GameOverControllerClass, TEXT("GameOverControllerClass wasn't set")))
	{
		return false;
	}

	GameOverController = NewObject<UGameOverController>(this, GameOverControllerClass);
	if (EnsureMsg(IsValid(GameOverController), TEXT("GameOverController cannot be created")))
	{
		GameOverController->Initialize(InGameWidget->GetGameOverWidget());
	}

	return true;
}
