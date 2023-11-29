// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyWeapon_Slower.h"

#include "Enemy.h"

void AEnergyWeapon_Slower::DamageEnemy()
{
	EnemyCharacter->TakeSlow(Slow);
}

void AEnergyWeapon_Slower::GetData(AEnemy* Enemy, const float TurretPerk)
{
	Slow = TurretPerk;
	Super::GetData(Enemy, TurretPerk);
}
