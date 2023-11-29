// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Slower.generated.h"
class AEnergyWeapon;

UCLASS()
class TOWERDEFENSE_API ATurret_Slower : public ATurret
{
	GENERATED_BODY()
	ATurret_Slower();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AEnergyWeapon> EnergyWeaponObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret Properties", meta=(AllowPrivateAccess="true"))
	float SlowFactor;

	AEnergyWeapon* EnergyWeapon;
};
