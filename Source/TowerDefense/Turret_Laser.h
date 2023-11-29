// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Laser.generated.h"
class AEnergyWeapon;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurret_Laser : public ATurret
{
	GENERATED_BODY()
	ATurret_Laser();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginPlay() override;

protected:
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void UpgradeTurret() override;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	TSubclassOf<AEnergyWeapon> EnergyWeaponObject;

	AEnergyWeapon* EnergyWeapn;
};
