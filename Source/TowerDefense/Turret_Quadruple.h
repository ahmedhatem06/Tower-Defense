// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Quadruple.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurret_Quadruple : public ATurret
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	ATurret_Quadruple();

protected:
	virtual void ConfigureNiagaraComponents() override;
	virtual void ShootAmmo(TSubclassOf<AActor> Projectile) override;
	virtual void ShootEnemy(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUpRight;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDownRight;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUpLeft;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDownLeft;
};
