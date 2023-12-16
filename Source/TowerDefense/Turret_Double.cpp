// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Double.h"

#include "Bullet.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"

ATurret_Double::ATurret_Double()
{
	ATurret_Double::ConfigureNiagaraComponents();
}

void ATurret_Double::ConfigureNiagaraComponents()
{
	NiagaraComponentUp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentUp"));
	NiagaraComponentUp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentUp->SetAutoActivate(false);

	NiagaraComponentDown = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentDown"));
	NiagaraComponentDown->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentDown->SetAutoActivate(false);
}

void ATurret_Double::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	Super::ShootAmmo(Projectile);
}

void ATurret_Double::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}

	if (FireCountdown <= 0.f)
	{
		ShootAmmo(Bullet);
		FireCountdown = 1.f / FireRate;
	}
	FireCountdown -= DeltaTime;
}
