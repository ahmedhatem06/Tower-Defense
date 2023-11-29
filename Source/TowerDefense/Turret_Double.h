// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Double.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurret_Double : public ATurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret_Double();
	virtual void BeginPlay() override;

protected:
	virtual void ConfigureArrowComponents() override;
	virtual void ConfigureNiagaraComponents() override;
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void DeactivateNiagaraComponent() override;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentUp;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentDown;

	UPROPERTY(VisibleAnywhere)
	TArray<UArrowComponent*> ArrowComponents;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDown;

	UPROPERTY(VisibleAnywhere)
	TArray<UNiagaraComponent*> NiagaraComponents;
};
