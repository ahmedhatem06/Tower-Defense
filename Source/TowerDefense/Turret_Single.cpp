// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Single.h"

#include "Bullet.h"
#include "NiagaraComponent.h"

ATurret_Single::ATurret_Single()
{
	ATurret_Single::ConfigureNiagaraComponents();
}

void ATurret_Single::ConfigureNiagaraComponents()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponent->SetAutoActivate(false);
}

void ATurret_Single::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	Super::ShootAmmo(Projectile);
}

void ATurret_Single::ShootEnemy(float DeltaTime)
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
