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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void ConfigureArrowComponents() override;
	virtual void ConfigureNiagaraComponents() override;
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void DeactivateNiagaraComponent() override;
	void RotateCanon(const float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponent;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CanonStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GunPointStaticMeshComponent;
};
