// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "GameFramework/Actor.h"
#include "ValuePickUp.generated.h"

UCLASS()
class CASTLEDEFENDER_API AValuePickUp : public APickUpBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AValuePickUp();

protected:

	UPROPERTY(EditAnywhere)
	float Value = 0;
};
