// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Air.h"

#include "Bullet.h"
#include "Enemy.h"
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
	ATurret_Air::ConfigureNiagaraComponents();
}

void ATurret_Air::ConfigureNiagaraComponents()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->AttachToComponent(GunPointStaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponent->SetAutoActivate(false);
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

	// Explicitly set pitch to ensure rotation only around the X-axis.
	CanonStaticMeshComponent->SetRelativeRotation(FRotator(-CannonRotation.Pitch, 0.0f, 0.0f));
}

void ATurret_Air::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	Super::ShootAmmo(Projectile);
}

void ATurret_Air::ShootEnemy(float DeltaTime)
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
