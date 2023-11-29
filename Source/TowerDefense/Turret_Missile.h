// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Turret_Missile.generated.h"
class AMissile;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATurret_Missile : public ATurret
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ATurret_Missile();
	virtual void BeginPlay() override;

protected:
	virtual void ConfigureArrowComponents() override;
	virtual void ConfigureNiagaraComponents() override;
	virtual void UpgradeTurret() override;
	virtual void Shoot() override;
	virtual void ShootEnemy(float DeltaTime) override;
	virtual void DeactivateNiagaraComponent() override;
	void LaunchTowards();

	FVector LaunchDirection;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentUp;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* TurretArrowComponentDown;

	UPROPERTY(VisibleAnywhere)
	TArray<UArrowComponent*> ArrowComponents;

	UPROPERTY(EditDefaultsOnly, Category= "Turret Properties")
	TSubclassOf<AMissile> Missile;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentUp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponentDown;

	UPROPERTY(VisibleAnywhere)
	TArray<UNiagaraComponent*> NiagaraComponents;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	float Speed = 1000.0f;
};
