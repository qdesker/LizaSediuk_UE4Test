// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "DataHolders/Gameplay/GameModes/GameModesData.h"
#include "GameOverWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_MULTICAST_DELEGATE(FOnBackButtonPressedDelegate);

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UGameOverWidget : public UDefaultUserWidget
{
	GENERATED_BODY()

public:

	virtual void BeginDestroy() override;

	void SetVictoryResult(EDefenceGameModeResult Result);

	FOnBackButtonPressedDelegate OnBackButtonPressed;

protected:

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnBackButtonPressedResult();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverResultVictory;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverResultDefeat;

	UPROPERTY(meta = (BindWidget))
	UButton* BackToMenuButton;
};
