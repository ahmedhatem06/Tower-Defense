// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Enemy_Ground.generated.h"

class AMyEnemyAIController;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemy_Ground : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Dead() override;
	void Arrived();

protected:
	// Declare a delegate for the timer callback
	FTimerDelegate AttackTimerDelegate;
	FTimerHandle AttackTimerHandle; // Declare the TimerHandle here

	UFUNCTION(BlueprintImplementableEvent)
	void StartAttackingBase();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyDead();
	FTimerHandle DestroyTimerHandle;

	UPROPERTY()
	AMyEnemyAIController* MyEnemyController;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	UAnimationAsset* DeadAnimation;
};
