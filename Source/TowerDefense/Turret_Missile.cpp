// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Missile.h"

#include "Enemy.h"
#include "Missile.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

ATurret_Missile::ATurret_Missile()
{
	ATurret_Missile::ConfigureArrowComponents();
	ATurret_Missile::ConfigureNiagaraComponents();
}

void ATurret_Missile::ConfigureArrowComponents()
{
	TurretArrowComponentUp = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentUp"));
	TurretArrowComponentUp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretArrowComponentDown = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponentDown"));
	TurretArrowComponentDown->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

void ATurret_Missile::UpgradeTurret()
{
	Damage += 5.f;
	Super::UpgradeTurret();
}

void ATurret_Missile::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UArrowComponent>(ArrowComponents);
	GetComponents<UNiagaraComponent>(NiagaraComponents);
}

void ATurret_Missile::LaunchTowards()
{
	LaunchDirection = FVector(Enemies[0]->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	TurretRangeStaticMeshComponent->SetPhysicsLinearVelocity(LaunchDirection * Speed);
}

void ATurret_Missile::Shoot()
{
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < ArrowComponents.Num(); i++)
	{
		if (AMissile* TempMissile = GetWorld()->SpawnActor<AMissile>(
			Missile, ArrowComponents[i]->GetComponentLocation(),
			Rotation))
		{
			TempMissile->GetData(Enemies[0], Damage);
			NiagaraComponents[i]->Activate();
		}
	}
	FTimerHandle NiagaraDeactivationTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret_Missile::DeactivateNiagaraComponent, 0.1f,
	                      false);
}

void ATurret_Missile::ShootEnemy(float DeltaTime)
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

void ATurret_Missile::DeactivateNiagaraComponent()
{
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->Deactivate();
	}
}
