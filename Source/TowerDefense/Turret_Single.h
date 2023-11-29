// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Single.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurret_Single : public ATurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret_Single();

	virtual void BeginPlay() override;

protected:
	virtual void ConfigureArrowComponents() override;
	virtual void ConfigureNiagaraComponents() override;
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void DeactivateNiagaraComponent() override;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponent;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;
};
