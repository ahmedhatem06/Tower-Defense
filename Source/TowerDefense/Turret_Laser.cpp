// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Laser.h"

#include "EnergyWeapon.h"

ATurret_Laser::ATurret_Laser()
{
}

void ATurret_Laser::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EnergyWeapon)
	{
		EnergyWeapon->Destroy();
	}
}

void ATurret_Laser::BeginPlay()
{
	Super::BeginPlay();
	const FRotator Rotation(0.0f, 0.0f, 0.0f);

	EnergyWeapon = GetWorld()->SpawnActor<AEnergyWeapon>(EnergyWeaponObject, GetActorLocation(),
	                                                     Rotation);
	EnergyWeapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	EnergyWeapon->GetTurret(this);
}

void ATurret_Laser::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	ShootEnergy();
}
