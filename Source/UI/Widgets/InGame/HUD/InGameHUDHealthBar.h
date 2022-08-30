// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "UObject/Object.h"
#include "InGameHUDHealthBar.generated.h"

class UCharacterHealthComponent;
class UTextBlock;
class UProgressBar;
/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UInGameHUDHealthBar : public UDefaultUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnHealthChanged();

	void ChangeState(float CurrentHealth, float InitialHealth);

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Health;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthValue;

	TWeakObjectPtr<UCharacterHealthComponent> HealthComponentWeakPtr;
};
