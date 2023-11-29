// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyWeapon.h"

#include "Enemy.h"
#include "Turret.h"

// Sets default values
AEnergyWeapon::AEnergyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void AEnergyWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetBeamLength(0);
}

// Called every frame
void AEnergyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyCharacter != nullptr)
	{
		TraceBeam();
	}

	CheckEnemy();
}

void AEnergyWeapon::GetData(AEnemy* Enemy, const float TurretPerk)
{
	//Damage = TurretDamage;
	EnemyCharacter = Enemy;

	SetActorTickEnabled(true);
}

void AEnergyWeapon::SetBeamLength(const float Length) const
{
	StaticMeshComponent->SetRelativeScale3D(FVector(Length / 100, StaticMeshComponent->GetRelativeScale3D().Y,
	                                                StaticMeshComponent->GetRelativeScale3D().Z));
}

void AEnergyWeapon::TraceBeam()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = EnemyCharacter->GetActorLocation();
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel
	(
		OUT HitResult,
		Start,
		End,
		ECC_GameTraceChannel1,
		CollisionQueryParams
	);

	if (bHit)
	{
		SetBeamLength(HitResult.Distance);
		DamageEnemy();
	}
	else
	{
		SetBeamLength(0);
	}
}

void AEnergyWeapon::GetTurret(ATurret* T)
{
	LaserTurret = T;
}

void AEnergyWeapon::DamageEnemy()
{
}

void AEnergyWeapon::CheckEnemy()
{
	if (!EnemyCharacter || EnemyCharacter->IsActorBeingDestroyed() || LaserTurret && !LaserTurret->HasEnemies())
	{
		SetActorTickEnabled(false);
		SetBeamLength(0);
		EnemyCharacter = nullptr;
	}
}
