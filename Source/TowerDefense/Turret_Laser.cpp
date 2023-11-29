// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Laser.h"

#include "EnergyWeapon.h"

ATurret_Laser::ATurret_Laser()
{
}

void ATurret_Laser::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EnergyWeapn)
	{
		EnergyWeapn->Destroy();
	}
}

void ATurret_Laser::BeginPlay()
{
	Super::BeginPlay();
	const FRotator Rotation(0.0f, 0.0f, 0.0f);

	EnergyWeapn = GetWorld()->SpawnActor<AEnergyWeapon>(EnergyWeaponObject, GetActorLocation(),
	                                                    Rotation);
	EnergyWeapn->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	EnergyWeapn->GetTurret(this);
}

void ATurret_Laser::Shoot()
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	EnergyWeapn->GetData(Enemies[0], Damage);
}

void ATurret_Laser::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	Shoot();
}

void ATurret_Laser::UpgradeTurret()
{
	Damage += 0.25f;
	Super::UpgradeTurret();
}
