// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"

void AAISpawnPoint::ProcessSpawn()
{
	if (!IsValid(GetWorld()) || !SpawnObject)
	{
		return;
	}

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = this;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto* NewPawn = GetWorld()->SpawnActor<APawn>(SpawnObject, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
	if (IsValid(NewPawn))
	{
		if (NewPawn->Controller == NULL)
		{
			NewPawn->SpawnDefaultController();
		}
	}
}
