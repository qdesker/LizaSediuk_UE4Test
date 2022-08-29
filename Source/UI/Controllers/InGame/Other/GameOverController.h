// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "DataHolders/Gameplay/GameModes/GameModesData.h"
#include "GameOverController.generated.h"

class UGameOverWidget;

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UGameOverController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual bool Initialize(UDefaultUserWidget* _Widget) override;
	virtual void BeginDestroy() override;

private:

	UFUNCTION()
	void OnGameOver(EDefenceGameModeResult Result);

	UFUNCTION()
	void OnBackToMenuPressed();

	UPROPERTY()
	UGameOverWidget* GameOverWidget;
};
