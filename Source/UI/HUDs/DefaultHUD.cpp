// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "UI/Widgets/DefaultUserWidget.h"
#include "UI/Controllers/WidgetController.h"

#include "Tools/MacroTools.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!EnsureMsg(MainWidgetClass, TEXT("[DefaultHUD] MainWidgetClass is not set")))
	{
		return;
	}

	MainWidget = CreateWidget<UDefaultUserWidget>(GetWorld(), MainWidgetClass);
	if (EnsureMsg(IsValid(MainWidget), TEXT("[DefaultHUD] MainWidget cannot be created")))
	{
		MainWidget->AddToViewport();
	}

	if (!EnsureMsg(MainWidgetControllerClass, TEXT("[DefaultHUD] MainWidgetControllerClass is not set")))
	{
		return;
	}

	MainController = NewObject<UWidgetController>(this, MainWidgetControllerClass);
	if (EnsureMsg(IsValid(MainController), TEXT("[DefaultHUD] MainController cannot be created")))
	{
		MainController->Initialize(MainWidget);
	}
}
