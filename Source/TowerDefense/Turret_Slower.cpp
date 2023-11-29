// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret_Slower.h"

#include "Enemy.h"
#include "EnergyWeapon.h"

ATurret_Slower::ATurret_Slower()
{
}

void ATurret_Slower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EnergyWeapon)
	{
		EnergyWeapon->Destroy();
	}
}

void ATurret_Slower::UpgradeTurret()
{
	SlowFactor += 0.25f;
	Super::UpgradeTurret();
}

void ATurret_Slower::BeginPlay()
{
	Super::BeginPlay();
	const FRotator Rotation(0.0f, 0.0f, 0.0f);

	EnergyWeapon = GetWorld()->SpawnActor<AEnergyWeapon>(EnergyWeaponObject, GetActorLocation(),
	                                                     Rotation);
	EnergyWeapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	EnergyWeapon->GetTurret(this);
}

void ATurret_Slower::Shoot()
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	EnergyWeapon->GetData(Enemies[0], SlowFactor);
}

void ATurret_Slower::ShootEnemy(float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	Shoot();
}

void ATurret_Slower::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AEnemy>())
	{
		CurrentEnemyCharacter = Cast<AEnemy>(OtherActor);
		CurrentEnemyCharacter->ResetSpeed();
		RemoveEnemy(CurrentEnemyCharacter);
	}
}
