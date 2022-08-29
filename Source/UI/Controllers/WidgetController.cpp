// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController.h"

#include "Tools/MacroTools.h"

bool UWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	if (!EnsureMsg(_Widget, TEXT("[WidgetController (%s)] Widget is nullptr"), *GetName()))
	{
		return false;
	}

	Widget = _Widget;

	return true;
}

void UWidgetController::BeginDestroy()
{
	SetTickEnabled(false);

	Super::BeginDestroy();
}

void UWidgetController::SetTickEnabled(bool IsEnabled)
{
	if (IsEnabled)
	{
		if (!EnsureMsg(!TickHandle.IsValid(), TEXT("[WidgetController] Attempt to enable tick twice. Tick is already enabled")))
		{
			return;
		}

		const auto TickDelegate = FTickerDelegate::CreateUObject(this, &UWidgetController::TickController);
		TickHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
	}
	else
	{
		FTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}
}
