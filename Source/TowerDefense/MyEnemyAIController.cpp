// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAIController.h"

#include "Enemy_Ground.h"
void AMyEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void AMyEnemyAIController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetPawn()->GetActorLocation();
	DistanceToTarget = FVector::Distance(CurrentLocation, NewTargetLocation);

	if (DistanceToTarget < 40.f)
	{
		StopMovement();

		if (AEnemy_Ground* EnemyCharacter = Cast<AEnemy_Ground>(GetPawn()))
		{
			EnemyCharacter->Arrived();
		}
		SetActorTickEnabled(false);
	}
}

void AMyEnemyAIController::MoveEnemy(const FVector& TargetLocation)
{
	const float RandomX = FMath::FRandRange(TargetLocation.X - 235, TargetLocation.X + 235);

	// Use the Y and Z coordinates from the AreaCenter
	const FVector RandomPoint(RandomX, TargetLocation.Y, TargetLocation.Z);
	MoveToLocation(RandomPoint);
	NewTargetLocation = RandomPoint;
	SetActorTickEnabled(true);
}
