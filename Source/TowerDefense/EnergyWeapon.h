// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyWeapon.generated.h"

class ATurret;
class AEnemy;

UCLASS()
class TOWERDEFENSE_API AEnergyWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnergyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetData(AEnemy* Enemy, float TurretPerk);
	void GetTurret(ATurret* T);

protected:
	UPROPERTY()
	AEnemy* EnemyCharacter;

	float BeamLength = 0.f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY()
	ATurret* LaserTurret;

	void SetBeamLength(float Length) const;

	void TraceBeam();

	virtual void DamageEnemy();

	void CheckEnemy();
};
