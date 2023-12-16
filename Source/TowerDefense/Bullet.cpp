// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BulletBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletBoxComponent"));
	BulletBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BulletBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
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

void ABullet::GetData(AEnemy* Enemy, const float TurretDamage)
{
	Damage = TurretDamage;
	EnemyCharacter = Enemy;

	SetActorTickEnabled(true);
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		AEnemy* CurrentEnemyCharacter = Cast<AEnemy>(OtherActor);
		CurrentEnemyCharacter->ReceiveDamage(Damage);
		Destroy();
	}
}
