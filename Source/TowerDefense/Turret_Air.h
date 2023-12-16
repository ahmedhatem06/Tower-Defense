// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Air.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurret_Air : public ATurret
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ATurret_Air();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void ConfigureNiagaraComponents() override;
	virtual void ShootAmmo(TSubclassOf<AActor> Projectile) override;
	virtual void ShootEnemy(float DeltaTime) override;
	void RotateCanon(const float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CanonStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GunPointStaticMeshComponent;
};
