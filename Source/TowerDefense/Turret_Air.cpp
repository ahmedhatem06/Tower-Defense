// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Air.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"

ATurret_Air::ATurret_Air()
{
	BaseStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMeshComponent"));
	BaseStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CanonStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanonStaticMeshComponent"));
	CanonStaticMeshComponent->AttachToComponent(BaseStaticMeshComponent,
	                                            FAttachmentTransformRules::KeepRelativeTransform);

	GunPointStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunPointtaticMeshComponent"));
	GunPointStaticMeshComponent->AttachToComponent(CanonStaticMeshComponent,
	                                               FAttachmentTransformRules::KeepRelativeTransform);
	ATurret_Air::ConfigureArrowComponents();
	ATurret_Air::ConfigureNiagaraComponents();
}

void ATurret_Air::ConfigureArrowComponents()
{
	TurretArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretArrowComponent"));
	TurretArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATurret_Air::ConfigureNiagaraComponents()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->AttachToComponent(GunPointStaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponent->SetAutoActivate(false);
}

void ATurret_Air::UpgradeTurret()
{
	Damage += 2.5f;
	Super::UpgradeTurret();
}

void ATurret_Air::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret_Air::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCanon(DeltaTime);
}

void ATurret_Air::RotateCanon(const float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}

	FVector CannonToPlaneDirection = Enemies[0]->GetActorLocation() - CanonStaticMeshComponent->
		GetComponentLocation();
	CannonToPlaneDirection.Normalize();
	// Calculate the rotation to align the cannon with the plane only on the X-axis.
	const FRotator CannonRotation = CannonToPlaneDirection.Rotation();
	//CannonRotation.Yaw = 0.0f; // Set yaw to 0 to keep the Y-axis fixed.
	//CannonRotation.Roll = 0.0f; // Set roll to 0 to keep the Z-axis fixed.

	// Explicitly set pitch to ensure rotation only around the X-axis.
	CanonStaticMeshComponent->SetRelativeRotation(FRotator(-CannonRotation.Pitch, 0.0f, 0.0f));
}

void ATurret_Air::Shoot()
{
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	if (ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(Bullet, TurretArrowComponent->GetComponentLocation(),
	                                                          Rotation))
	{
		TempBullet->GetData(Enemies[0], Damage);
		NiagaraComponent->Activate();
		FTimerHandle NiagaraDeactivationTimerHandle;
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret_Air::DeactivateNiagaraComponent, 0.1f,
		                      false);
	}
}

void ATurret_Air::ShootEnemy(float DeltaTime)
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

void ATurret_Air::DeactivateNiagaraComponent()
{
	NiagaraComponent->Deactivate();
}
