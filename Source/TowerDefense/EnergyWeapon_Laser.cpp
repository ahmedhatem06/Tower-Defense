// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyWeapon_Laser.h"

#include "Enemy.h"

void AEnergyWeapon_Laser::DamageEnemy()
{
	EnemyCharacter->ReceiveDamage(Damage);
}

void AEnergyWeapon_Laser::GetData(AEnemy* Enemy, const float TurretPerk)
{
	Damage = TurretPerk;
	Super::GetData(Enemy, TurretPerk);
}
