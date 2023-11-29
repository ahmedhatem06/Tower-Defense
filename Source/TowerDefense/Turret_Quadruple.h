// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Quadruple.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurret_Quadruple : public ATurret
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	ATurret_Quadruple();
	virtual void BeginPlay() override;

protected:
	virtual void ConfigureArrowComponents() override;
	virtual void ConfigureNiagaraComponents() override;
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void DeactivateNiagaraComponent() override;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentUpRight;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentDownRight;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentUpLeft;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentDownLeft;

	UPROPERTY(VisibleAnywhere)
	TArray<UArrowComponent*> ArrowComponents;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUpRight;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDownRight;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUpLeft;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDownLeft;

	UPROPERTY(VisibleAnywhere)
	TArray<UNiagaraComponent*> NiagaraComponents;
};
