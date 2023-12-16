// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretDataAsset.h"

float UTurretDataAsset::GetDamage() const
{
	return Damage;
}

float UTurretDataAsset::GetUpgradeDamage() const
{
	return UpgradeDamage;
}

float UTurretDataAsset::GetRadius() const
{
	return Radius;
}

float UTurretDataAsset::GetFireRate() const
{
	return FireRate;
}

float UTurretDataAsset::GetRotationSpeed() const
{
	return RotationSpeed;
}

int UTurretDataAsset::GetPrice() const
{
	return Price;
}

float UTurretDataAsset::GetUpgradePrice() const
{
	return UpgradePrice;
}

int UTurretDataAsset::GetSellPrice() const
{
	return SellPrice;
}

EEnemyType UTurretDataAsset::GetShootType() const
{
	return ShootType;
}

TSubclassOf<ATurret> UTurretDataAsset::GetTurret() const
{
	return Turret;
}

UTexture2D* UTurretDataAsset::GetTexture() const
{
	return Texture;
}

FString UTurretDataAsset::GetCurrency() const
{
	return Currency;
}
