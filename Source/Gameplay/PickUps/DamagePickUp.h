// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValuePickUp.h"
#include "GameFramework/Actor.h"
#include "DamagePickUp.generated.h"

UCLASS()
class CASTLEDEFENDER_API ADamagePickUp : public AValuePickUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamagePickUp();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
