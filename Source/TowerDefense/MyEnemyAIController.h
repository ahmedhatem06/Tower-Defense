// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AMyEnemyAIController : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void MoveEnemy(const FVector& TargetLocation);

protected:
	FVector CurrentLocation;
	FVector NewTargetLocation;
	float DistanceToTarget;
};
