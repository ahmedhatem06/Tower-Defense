// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Double.generated.h"

UCLASS()
class TOWERDEFENSE_API ATurret_Double : public ATurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret_Double();

protected:
	virtual void ConfigureNiagaraComponents() override;
	virtual void ShootAmmo(TSubclassOf<AActor> Projectile) override;
	virtual void ShootEnemy(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDown;
};
