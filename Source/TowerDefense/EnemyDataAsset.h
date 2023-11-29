// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

enum class EEnemyType;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	FVector TargetLocation;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float Speed;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	int Price;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	int MinSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float StartSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	float DamageRate = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	EEnemyType EnemyTpe;

public:
	FVector GetTargetLocation() const;
	float GetDamage() const;
	float GetSpeed() const;
	float GetHealth() const;
	float GetMaxHealth() const;
	int GetPrice() const;
	int GetMinSpeed() const;
	float GetStartSpeed() const;
	float GetDamageRate() const;
	EEnemyType GetEnemyType() const;
};
