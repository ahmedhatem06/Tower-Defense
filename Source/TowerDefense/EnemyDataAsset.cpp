// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDataAsset.h"

FVector UEnemyDataAsset::GetTargetLocation() const
{
	return TargetLocation;
}

float UEnemyDataAsset::GetDamage() const
{
	return Damage;
}

float UEnemyDataAsset::GetSpeed() const
{
	return Speed;
}

float UEnemyDataAsset::GetHealth() const
{
	return Health;
}

float UEnemyDataAsset::GetMaxHealth() const
{
	return MaxHealth;
}

int UEnemyDataAsset::GetPrice() const
{
	return Price;
}

int UEnemyDataAsset::GetMinSpeed() const
{
	return MinSpeed;
}

float UEnemyDataAsset::GetStartSpeed() const
{
	return StartSpeed;
}

float UEnemyDataAsset::GetDamageRate() const
{
	return DamageRate;
}

EEnemyType UEnemyDataAsset::GetEnemyType() const
{
	return EnemyTpe;
}
