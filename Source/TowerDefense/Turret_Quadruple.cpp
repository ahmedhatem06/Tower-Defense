// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Quadruple.h"

#include "Bullet.h"
#include "NiagaraComponent.h"

ATurret_Quadruple::ATurret_Quadruple()
{
	ATurret_Quadruple::ConfigureNiagaraComponents();
}

void ATurret_Quadruple::ConfigureNiagaraComponents()
{
	NiagaraComponentUpRight = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentUpRight"));
	NiagaraComponentUpRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentUpRight->SetAutoActivate(false);

	NiagaraComponentDownRight = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentDownRight"));
	NiagaraComponentDownRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentDownRight->SetAutoActivate(false);

	NiagaraComponentUpLeft = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentUpLeft"));
	NiagaraComponentUpLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentUpLeft->SetAutoActivate(false);

	NiagaraComponentDownLeft = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentDownLeft"));
	NiagaraComponentDownLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentDownLeft->SetAutoActivate(false);
}

void ATurret_Quadruple::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	Super::ShootAmmo(Projectile);
}

void ATurret_Quadruple::ShootEnemy(float DeltaTime)
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
