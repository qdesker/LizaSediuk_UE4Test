// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Characters/DefaultCharacter.h"
#include "AICharacter.generated.h"

class UEnemyAnalyzerComponent;

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API AAICharacter : public ADefaultCharacter
{
	GENERATED_BODY()

public:

	AAICharacter();

	UFUNCTION(BlueprintCallable)
	void SetCurrentTarget(AActor* Target) { CurrentTarget = Target; }
	/** The actor with which the AI will interact (in most cases - attack) */
	const AActor* GetCurrentTarget() const { return CurrentTarget; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Analyzers")
	UEnemyAnalyzerComponent* EnemyAnalyzer;

	virtual void OnDead() override;

private:

	UPROPERTY()
	AActor* CurrentTarget;
};
