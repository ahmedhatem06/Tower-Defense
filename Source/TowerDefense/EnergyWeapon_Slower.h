// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyWeapon.h"
#include "EnergyWeapon_Slower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnergyWeapon_Slower : public AEnergyWeapon
{
	GENERATED_BODY()

protected:
	virtual void DamageEnemy() override;
	virtual void GetData(AEnemy* Enemy, float TurretPerk) override;

	float Slow;
};
