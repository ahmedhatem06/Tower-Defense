// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Single.h"

#include "Bullet.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"

ATurret_Single::ATurret_Single()
{
	ATurret_Single::ConfigureArrowComponents();
	ATurret_Single::ConfigureNiagaraComponents();
}

void ATurret_Single::ConfigureArrowComponents()
{
	TurretArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponent"));
	TurretArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATurret_Single::ConfigureNiagaraComponents()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponent->SetAutoActivate(false);
}

void ATurret_Single::UpgradeTurret()
{
	Damage += 2.5f;
	Super::UpgradeTurret();
}

void ATurret_Single::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret_Single::Shoot()
{
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	if (ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(Bullet, TurretArrowComponent->GetComponentLocation(),
	                                                          Rotation))
	{
		TempBullet->GetData(Enemies[0], Damage);
		NiagaraComponent->Activate();
		FTimerHandle NiagaraDeactivationTimerHandle;
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret_Single::DeactivateNiagaraComponent, 0.1f,
		                      false);
	}
}

void ATurret_Single::ShootEnemy(float DeltaTime)
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

void ATurret_Single::DeactivateNiagaraComponent()
{
	NiagaraComponent->Deactivate();
}
