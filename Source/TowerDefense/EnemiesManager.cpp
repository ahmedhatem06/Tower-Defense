// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesManager.h"

#include "MyHUD.h"


AEnemiesManager* AEnemiesManager::Instance = nullptr;
// Gets the singleton instance of the ACurrency class.
AEnemiesManager* AEnemiesManager::GetInstance()
{
	return Instance;
}

// Sets default values
AEnemiesManager::AEnemiesManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemiesManager::BeginPlay()
{
	Super::BeginPlay();
	Instance = this;
	OnEnemyDestroyEvent.AddDynamic(this, &AEnemiesManager::HandleEnemyDestroyEvent);
	//StartWave();
}

int AEnemiesManager::GetAliensKilled() const
{
	return AliensKilled;
}

void AEnemiesManager::HandleEnemyDestroyEvent(const bool bIsExploded)
{
	EnemiesAlive--;
	if (!bIsExploded)
	{
		AliensKilled++;
		const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		MyHUD->AlienDead(AliensKilled);
	}
}

int AEnemiesManager::EnemiesPerWave() const
{
	return FMath::RoundToInt(BaseEnemies * FMath::Pow(CurrentWave, DifficultyScalingFactor));
}

void AEnemiesManager::StartWave()
{
	EnemiesAlive = 0;
	IsSpawning = true;
	SetActorTickEnabled(true);
	EnemiesLeftToSpawn = EnemiesPerWave();
	AlienProbability = EnemiesLeftToSpawn / TankProbability;
	EnemiesInCurrentWave = EnemiesLeftToSpawn;
}

void AEnemiesManager::EndWave()
{
	DecreaseEnemiesPerSecond();
	IsSpawning = false;
	TimeSinceLastSpawn = 0;
	CurrentWave++;
	const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->UpdateWaveText(CurrentWave);
	MyHUD->WaveCountdown(TimeBetweenWaves);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemiesManager::StartWave, TimeBetweenWaves, false);
	SetActorTickEnabled(false);
}

void AEnemiesManager::SpawnEnemy()
{
	const bool ShouldSpawnEnemy0 = FMath::RandBool();
	const bool bSpawnPlane = FMath::RandBool();

	const float GroundRandomXSpawnPoint = FMath::FRandRange(GroundEnemiesStartPosition.X - 150,
	                                                        GroundEnemiesStartPosition.X + 150);
	const FVector GroundEnemySpawnPoint(GroundRandomXSpawnPoint, GroundEnemiesStartPosition.Y,
	                                    GroundEnemiesStartPosition.Z);

	const float AirRandomXSpawnPoint = FMath::FRandRange(AirEnemiesStartPosition.X - 1000,
	                                                     AirEnemiesStartPosition.X + 1000);
	const FVector AirEnemySpawnPoint(AirRandomXSpawnPoint, AirEnemiesStartPosition.Y,
	                                 AirEnemiesStartPosition.Z);
	if (ShouldSpawnEnemy0)
	{
		if (bSpawnPlane)
		{
			GetWorld()->SpawnActor<AActor>(AirEnemies[0], AirEnemySpawnPoint, FRotator(0.0f, 0.0f, 0.0f));
		}
		else
		{
			GetWorld()->SpawnActor<AActor>(GroundEnemies[0], GroundEnemySpawnPoint, FRotator(0.0f, 0.0f, 0.0f));
		}
	}
	else
	{
		if (bSpawnPlane)
		{
			GetWorld()->SpawnActor<AActor>(AirEnemies[1], AirEnemySpawnPoint, FRotator(0.0f, 0.0f, 0.0f));
		}
		else
		{
			GetWorld()->SpawnActor<AActor>(GroundEnemies[1], GroundEnemySpawnPoint, FRotator(0.0f, 0.0f, 0.0f));
		}
	}

	if ((EnemiesInCurrentWave / 2) > EnemiesLeftToSpawn && AlienProbability >= 1)
	{
		GetWorld()->SpawnActor<AActor>(GroundEnemies[2], GroundEnemySpawnPoint, FRotator(0.0f, 0.0f, 0.0f));
		AlienProbability -= 1;
		EnemiesAlive++;
	}
}

void AEnemiesManager::DecreaseEnemiesPerSecond()
{
	if (CurrentWave >= 3)
	{
		if (EnemiesPerSecond > 0.25f)
		{
			EnemiesPerSecond -= 0.1f;
		}
		DifficultyScalingFactor += 0.1f;
	}
}

// Called every frame
void AEnemiesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsSpawning)
	{
		return;
	}
	TimeSinceLastSpawn += DeltaTime;

	if (TimeSinceLastSpawn >= EnemiesPerSecond && EnemiesLeftToSpawn > 0)
	{
		SpawnEnemy();
		EnemiesLeftToSpawn--;
		EnemiesAlive++;
		TimeSinceLastSpawn = 0.f;
	}

	if (EnemiesAlive == 0 && EnemiesLeftToSpawn == 0)
	{
		EndWave();
	}
}
