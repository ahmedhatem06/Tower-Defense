// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Missile.h"

#include "Enemy.h"
#include "NiagaraComponent.h"

ATurret_Missile::ATurret_Missile()
{
	ATurret_Missile::ConfigureNiagaraComponents();
}

void ATurret_Missile::ConfigureNiagaraComponents()
{
	NiagaraComponentUp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentUp"));
	NiagaraComponentUp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentUp->SetAutoActivate(false);

	NiagaraComponentDown = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponentDown"));
	NiagaraComponentDown->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponentDown->SetAutoActivate(false);
}

void ATurret_Missile::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	Super::ShootAmmo(Projectile);
}

void ATurret_Missile::LaunchTowards()
{
	LaunchDirection = FVector(Enemies[0]->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	TurretRangeStaticMeshComponent->SetPhysicsLinearVelocity(LaunchDirection * Speed);
}

void ATurret_Missile::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}

	if (FireCountdown <= 0.f)
	{
		ShootAmmo(Missile);
		FireCountdown = 1.f / FireRate;
	}
	FireCountdown -= DeltaTime;
}
