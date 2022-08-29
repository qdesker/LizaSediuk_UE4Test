// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "InGameHUDController.generated.h"

class UInGameHUDWidget;

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UInGameHUDController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual bool Initialize(UDefaultUserWidget* _Widget) override;
	virtual void BeginDestroy() override;

protected:

	virtual bool TickController(float DeltaTime) override;

private:

	void SetTimerValue(float ValueInSeconds);

	void UpdateMissionInfo();
	void UpdateCurrentWeaponInfo(EWeaponType Type);

	void SubscribeOnWeaponChanged();
	void UnsubscribeOnWeaponChanged();

	UPROPERTY()
	UInGameHUDWidget* InGameHUDWidget;
};
