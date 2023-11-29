// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Quadruple.h"

#include "Bullet.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

ATurret_Quadruple::ATurret_Quadruple()
{
	ATurret_Quadruple::ConfigureArrowComponents();
	ATurret_Quadruple::ConfigureNiagaraComponents();
}

void ATurret_Quadruple::ConfigureArrowComponents()
{
	TurretArrowComponentUpRight = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentUpRight"));
	TurretArrowComponentUpRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretArrowComponentDownRight = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponentDownRight"));
	TurretArrowComponentDownRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretArrowComponentUpLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentUpLeft"));
	TurretArrowComponentUpLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretArrowComponentDownLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentDownLeft"));
	TurretArrowComponentDownLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

void ATurret_Quadruple::UpgradeTurret()
{
	Damage += 2.5f;
	Super::UpgradeTurret();
}

void ATurret_Quadruple::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UArrowComponent>(ArrowComponents);
	GetComponents<UNiagaraComponent>(NiagaraComponents);
}

void ATurret_Quadruple::Shoot()
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
	TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret_Quadruple::DeactivateNiagaraComponent, 0.1f,
	                      false);
}

void ATurret_Quadruple::ShootEnemy(float DeltaTime)
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

void ATurret_Quadruple::DeactivateNiagaraComponent()
{
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->Deactivate();
	}
}
