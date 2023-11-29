// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurretDataAsset.generated.h"

class ATurret;
enum class EEnemyType;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTurretDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	float Radius = 500.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	float FireRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	float RotationSpeed = 4.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	int Price = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	int UpgradePrice = 150;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	int SellPrice = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	EEnemyType ShootType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Data", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ATurret> Turret;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Data", meta=(AllowPrivateAccess="true"))
	UTexture2D* Texture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Data", meta=(AllowPrivateAccess="true"))
	FString Currency = "";

public:
	float GetDamage() const;
	float GetRadius() const;
	float GetFireRate() const;
	float GetRotationSpeed() const;
	int GetPrice() const;
	float GetUpgradePrice() const;
	int GetSellPrice() const;
	EEnemyType GetShootType() const;
	TSubclassOf<ATurret> GetTurret() const;
	UTexture2D* GetTexture() const;
	FString GetCurrency()const;
};
