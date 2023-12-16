// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Missile.generated.h"
class AMissile;

UCLASS()
class TOWERDEFENSE_API ATurret_Missile : public ATurret
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ATurret_Missile();

protected:
	virtual void ConfigureNiagaraComponents() override;
	virtual void ShootAmmo(TSubclassOf<AActor> Projectile) override;
	virtual void ShootEnemy(float DeltaTime) override;
	void LaunchTowards();

	FVector LaunchDirection;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDown;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	float Speed = 1000.0f;
};
