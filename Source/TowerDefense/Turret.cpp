// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Bullet.h"
#include "Enemy.h"
#include "EnergyWeapon.h"
#include "Missile.h"
#include "NiagaraComponent.h"
#include "TurretDataAsset.h"
#include "TurretPlacement.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	TurretSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TurretSphereComponent"));
	TurretSphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TurretSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretSkeletalMeshComponent"));
	TurretSkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TurretSkeletalMeshComponent->OnClicked.AddUniqueDynamic(this, &ATurret::ATurret::OnTurretClicked);

	TurretSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	TurretSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);

	TurretRangeStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("TurretRangeStaticMeshComponent"));
	TurretRangeStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TurretRangeStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ATurret::ConfigureNiagaraComponents();
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	GetTurretData();

	GetComponents<UNiagaraComponent>(NiagaraComponents);

	TurretSphereComponent->SetSphereRadius(Radius);
	const float RangeFactor = Radius / 50.f;
	const FVector RangeScale = FVector(RangeFactor, RangeFactor, RangeFactor);
	TurretRangeStaticMeshComponent->SetWorldScale3D(RangeScale);

	TurretPlacement = ATurretPlacement::GetInstance();
}

// Called every frame
void ATurret::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurret(DeltaTime);

	ShootEnemy(DeltaTime);
}

void ATurret::RotateTurret(const float DeltaTime)
{
	if (Enemies.Num() == 0)
	{
		return;
	}
	const FVector Direction = GetActorLocation() - Enemies[0]->GetActorLocation();
	const FRotator PlayerRot = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorLocation(GetActorLocation());
	const FRotator InterpolatedLocation = UKismetMathLibrary::RInterpTo(
		GetActorRotation(), PlayerRot, DeltaTime, RotationSpeed);
	const FRotator NewRotator = FRotator(GetActorRotation().Pitch, InterpolatedLocation.Yaw, InterpolatedLocation.Roll);
	SetActorRotation(NewRotator);
}

void ATurret::ShootEnemy(const float DeltaTime)
{
}

void ATurret::ShootAmmo(const TSubclassOf<AActor> Projectile)
{
	const FRotator Rotation(0.0f, 0.0f, 0.0f);

	//Skipping the first 3 as they are bones, not sockets.
	for (int32 i = 0; i < SocketNames.Num(); ++i)
	{
		FVector SocketPosition = TurretSkeletalMeshComponent->GetSocketLocation(SocketNames[i]);
		if (AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(Projectile, SocketPosition,
		                                                               Rotation))
		{
			if (SpawnedProjectile->IsA(ABullet::StaticClass()))
			{
				ABullet* SpawnedBullet = Cast<ABullet>(SpawnedProjectile);
				SpawnedBullet->GetData(Enemies[0], Damage);
				// The spawned actor is either an instance of ABullet or AMissile
				// Perform specific actions for ABullet or AMissile
			}
			else if (SpawnedProjectile->IsA(AMissile::StaticClass()))
			{
				AMissile* SpawnedMissile = Cast<AMissile>(SpawnedProjectile);
				SpawnedMissile->GetData(Enemies[0], Damage);
			}
			NiagaraComponents[i]->Activate();
		}
	}

	FTimerHandle NiagaraDeactivationTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(NiagaraDeactivationTimerHandle, this, &ATurret::DeactivateNiagaraComponent, 0.1f,
	                      false);
}

void ATurret::ShootEnergy()
{
	EnergyWeapon->GetData(Enemies[0], Damage);
}

void ATurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		CurrentEnemyCharacter = Cast<AEnemy>(OtherActor);
		if (CurrentEnemyCharacter->GetEnemyType() == ShootType)
		{
			Enemies.Add(CurrentEnemyCharacter);
		}
	}
}

void ATurret::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AEnemy>())
	{
		CurrentEnemyCharacter = Cast<AEnemy>(OtherActor);
		if (CurrentEnemyCharacter->GetEnemyType() == ShootType)
		{
			RemoveEnemy(CurrentEnemyCharacter);
		}
	}
}

void ATurret::Initialize(ATurretTile* TT)
{
	TurretSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	IsTurretPlaced = true;
	TurretSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RangeVisibility(false);
	TurretTile = TT;
}

void ATurret::GetTurretData()
{
	Damage = TurretDataAsset->GetDamage();
	UpgradeDamage = TurretDataAsset->GetUpgradeDamage();
	Radius = TurretDataAsset->GetRadius();
	FireRate = TurretDataAsset->GetFireRate();
	RotationSpeed = TurretDataAsset->GetRotationSpeed();
	Price = TurretDataAsset->GetPrice();
	UpgradePrice = TurretDataAsset->GetUpgradePrice();
	SellPrice = TurretDataAsset->GetSellPrice();
	ShootType = TurretDataAsset->GetShootType();
}

void ATurret::OnTurretClicked(UPrimitiveComponent* pComponent, FKey inKey)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("1"));
	if (IsTurretPlaced && !TurretPlacement->IsPlacingTurret())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("2"));
		TurretPlacement->StartTurretSelection(this, false);
	}
}

void ATurret::RangeVisibility(const bool Visible)
{
	TurretRangeStaticMeshComponent->SetVisibility(Visible);
}

int ATurret::GetPrice()
{
	return Price;
}

int ATurret::GetUpgradePrice()
{
	return UpgradePrice;
}

int ATurret::GetSellPrice()
{
	return SellPrice;
}

void ATurret::UpgradeTurret()
{
	Damage += UpgradeDamage;
	RankLevel++;
	TurretPlacement->StartTurretSelection(this, true);
}

void ATurret::SellTurret()
{
	Destroy();
}

int ATurret::GetRange()
{
	return Radius;
}

int ATurret::GetDamage()
{
	return Damage;
}

int ATurret::GetFireRate()
{
	return FireRate;
}

int ATurret::GetRankLevel()
{
	return RankLevel;
}

EEnemyType ATurret::GetTurretType()
{
	return ShootType;
}

ATurretTile* ATurret::GetTurretTile() const
{
	return TurretTile;
}

void ATurret::ConfigureNiagaraComponents()
{
}

void ATurret::DeactivateNiagaraComponent()
{
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->Deactivate();
	}
}

void ATurret::ConfigureSockets()
{
}

bool ATurret::HasEnemies() const
{
	return (Enemies.Num() > 0);
}

void ATurret::RemoveEnemy(const AEnemy* Enemy)
{
	for (int i = 0; i < Enemies.Num(); i++)
	{
		if (Enemy == Enemies[i])
		{
			Enemies.RemoveAt((i));
		}
	}
}
