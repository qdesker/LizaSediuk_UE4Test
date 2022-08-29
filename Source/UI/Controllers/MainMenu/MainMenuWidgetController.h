// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "MainMenuWidgetController.generated.h"

class UMainMenuWidget;

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UMainMenuWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual bool Initialize(UDefaultUserWidget* _Widget) override;
	virtual void BeginDestroy() override;

private:

	UFUNCTION()
	void OnPlayClicked();

	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;
};
