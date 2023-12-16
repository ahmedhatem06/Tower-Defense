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
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex) override;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	TSubclassOf<AEnergyWeapon> EnergyWeaponObject;
};
