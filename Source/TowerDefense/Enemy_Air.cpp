// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Air.h"

#include "EnemiesManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"

AEnemy_Air::AEnemy_Air()
{
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemy_Air::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();

	CurrentLocation = GetActorLocation();

	const FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	// Calculate the rotation to look at the target direction
	const FRotator TargetRotation = Direction.Rotation();

	// Interpolate the current rotation to the target rotation for smoother rotation
	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, 1, RotationSpeed);

	// Set the new rotation for the character
	SetActorRotation(NewRotation);
}

void AEnemy_Air::Tick(float DeltaTime)
{
	if (!TargetLocation.IsNearlyZero())
	{
		// Calculate the direction from the current location to the target location
		const FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();

		// Calculate the new location based on the move speed and delta time
		const FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;

		// Set the new location for the character
		SetActorLocation(NewLocation);

		// Check the distance between the current location and the target location

		// Check if the character has reached the target location (within 100 units)
		if (const float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation); DistanceToTarget < 50.0f)
		{
			// Optionally, you can perform additional actions when the target is reached
			TargetLocation = FVector::ZeroVector;
			Explode();
		}
	}
}

void AEnemy_Air::Dead()
{
	Destroy();
}

void AEnemy_Air::Explode()
{
	HealthWidgetComponent->SetVisibility(false);

	EnemyCapsuleComponent = FindComponentByClass<UCapsuleComponent>();
	EnemyCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ParticleSystemComponent->Activate();

	const AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
	EnemiesManager->OnEnemyDestroyEvent.Broadcast(true);

	DamageBase();

	SkeletalMesh->SetVisibility(false);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy_Air::DestroyAirEnemy, 1.0f, false);
}

void AEnemy_Air::DestroyAirEnemy()
{
	Destroy();
}
