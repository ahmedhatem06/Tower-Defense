// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretTile.h"

#include "TurretPlacement.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

// Sets default values
ATurretTile::ATurretTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent->OnBeginCursorOver.AddDynamic(this, &ATurretTile::OnBoxBeginCursorOver);
	BoxComponent->OnEndCursorOver.AddDynamic(this, &ATurretTile::OnBoxEndCursorOver);
	BoxComponent->SetGenerateOverlapEvents(true);
}

void ATurretTile::TurretStatus(const bool Status)
{
	HasTurret = Status;

	if (HasTurret)
	{
		ChangeTileMaterial(GreenMaterial);
	}
	else
	{
		ChangeTileMaterial(BlueMaterial);
	}
}

void ATurretTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ATurretTile::OnBoxBeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
	if (!HasTurret)
	{
		TurretPlacement = ATurretPlacement::GetInstance();
		if (TurretPlacement != nullptr)
		{
			TurretPlacement->LockTurret(ArrowComponent->GetComponentLocation(), true, this);
		}
		ChangeTileMaterial(GreenMaterial);
	}
}

void ATurretTile::OnBoxEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	if (!HasTurret)
	{
		TurretPlacement = ATurretPlacement::GetInstance();
		if (TurretPlacement != nullptr)
		{
			TurretPlacement->LockTurret(ArrowComponent->GetComponentLocation(), false, this);
		}
		ChangeTileMaterial(BlueMaterial);
	}
}

// Called when the game starts or when spawned
void ATurretTile::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretTile::ChangeTileMaterial(UMaterial* Material) const
{
	StaticMeshComponent->SetMaterial(0, Material);
}
