// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemiesManager.generated.h"
class ATowerBase;
class AEnemy;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestroy, bool, bIsEnemyExploded);

UCLASS()
class TOWERDEFENSE_API AEnemiesManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemiesManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	TArray<TSubclassOf<AEnemy>> GroundEnemies;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	TArray<TSubclassOf<AEnemy>> AirEnemies;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	FVector GroundEnemiesStartPosition;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	FVector AirEnemiesStartPosition;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	int BaseEnemies = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	float EnemiesPerSecond = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	float TimeBetweenWaves = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	float DifficultyScalingFactor = 0.75f;

	UPROPERTY(EditDefaultsOnly, Category = "Wave Data")
	float TankProbability = 10.f;

	int CurrentWave = 1;

	float TimeSinceLastSpawn = 0;

	int EnemiesAlive = 0;

	int EnemiesLeftToSpawn = 0;

	bool IsSpawning = false;

	int AlienProbability = 0;

	float EnemiesInCurrentWave = 0;

	int AliensKilled = 0;

	UFUNCTION()
	void HandleEnemyDestroyEvent(bool bIsExploded);

	int EnemiesPerWave() const;

	void EndWave();

	void SpawnEnemy();

	void DecreaseEnemiesPerSecond();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FOnEnemyDestroy OnEnemyDestroyEvent;

	int GetAliensKilled() const;

	void StartWave();

	UPROPERTY(EditAnywhere, Category = "Wave Data")
	ATowerBase* TowerBase;

	static AEnemiesManager* GetInstance();

private:
	static AEnemiesManager* Instance;
};
