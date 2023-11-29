// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	MissileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnOverlapBegin);

	ProjectileMovementComponent = CreateDefaultSubobject<
		UProjectileMovementComponent>(TEXT("MissileMovementComponent"));
	ProjectileMovementComponent->bIsHomingProjectile = true;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EnemyCharacter != nullptr)
	{
		const FRotator TargetRotation = (EnemyCharacter->GetActorLocation() - GetActorLocation()).Rotation();
		const FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime,
		                                                       RotationSpeed);
		SetActorRotation(InterpolatedRotation);
		const FVector InterpolatedLocation = UKismetMathLibrary::VInterpTo(
			GetActorLocation(), EnemyCharacter->GetActorLocation(), DeltaTime,
			MoveSpeed);
		SetActorLocation(InterpolatedLocation);
	}

	if (EnemyCharacter != nullptr && EnemyCharacter->IsActorBeingDestroyed() || EnemyCharacter->IsDead())
	{
		Destroy();
	}
}

void AMissile::GetData(AEnemy* Enemy, float TurretDamage)
{
	Damage = TurretDamage;
	EnemyCharacter = Enemy;
	ProjectileMovementComponent->HomingTargetComponent = EnemyCharacter->MissileArrowComponent;
	ProjectileMovementComponent->Activate();
	SetActorTickEnabled(true);
}

void AMissile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		AEnemy* CurrentEnemyCharacter = Cast<AEnemy>(OtherActor);
		CurrentEnemyCharacter->TakeDamage(Damage);
		Destroy();
	}
}

void AMissile::LaunchTowards(const FVector& TargetLocation)
{
	LaunchDirection = FVector(TargetLocation - GetActorLocation()).GetSafeNormal();
	MissileMesh->SetPhysicsLinearVelocity(LaunchDirection * MoveSpeed);
}
