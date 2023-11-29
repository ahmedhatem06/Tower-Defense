// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Double.h"

#include "Bullet.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

ATurret_Double::ATurret_Double()
{
	ATurret_Double::ConfigureArrowComponents();
	ATurret_Double::ConfigureNiagaraComponents();
}

void ATurret_Double::ConfigureArrowComponents()
{
	TurretArrowComponentUp = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentUp"));
	TurretArrowComponentUp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretArrowComponentDown = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentDown"));
	TurretArrowComponentDown->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

void ATurret_Double::UpgradeTurret()
{
	Damage += 2.5f;
	Super::UpgradeTurret();
}

void ATurret_Double::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UArrowComponent>(ArrowComponents);
	GetComponents<UNiagaraComponent>(NiagaraComponents);
}

void ATurret_Double::Shoot()
{
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < ArrowComponents.Num(); i++)
	{
		if (ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(Bullet, ArrowComponents[i]->GetComponentLocation(),
		                                                          Rotation))
		{
			TempBullet->GetData(Enemies[0], Damage);
			NiagaraComponents[i]->Activate();
		}
	}
	FTimerHandle NiagaraDeactivationTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret_Double::DeactivateNiagaraComponent, 0.1f,
	                      false);
}

void ATurret_Double::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}

	if (FireCountdown <= 0.f)
	{
		Shoot();
		FireCountdown = 1.f / FireRate;
	}
	FireCountdown -= DeltaTime;
}

void ATurret_Double::DeactivateNiagaraComponent()
{
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->Deactivate();
	}
}
