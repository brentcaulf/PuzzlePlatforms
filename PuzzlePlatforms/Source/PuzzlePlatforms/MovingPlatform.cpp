// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	// if this is called on the server (HasAuthority), replicate the actor and it's movement
	if (HasAuthority())
	{
		// replicates the entire actor
		SetReplicates(true);
		// replicate the actor's movement
		SetReplicateMovement(true);
	}
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(MovementSpeed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}

}
