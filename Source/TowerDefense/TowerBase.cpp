// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"

// Sets default values
ATowerBase::ATowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	RightStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightStaticMeshComponent"));
	RightStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LeftStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftStaticMeshComponent"));
	LeftStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LeftDynamicMaterialInstance = nullptr;
	RightDynamicMaterialInstance = nullptr;
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	if (OriginalMaterial)
	{
		// Create a dynamic material instance based on the assigned material
		RightDynamicMaterialInstance = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
		RightStaticMeshComponent->SetMaterial(1, RightDynamicMaterialInstance);

		LeftDynamicMaterialInstance = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
		LeftStaticMeshComponent->SetMaterial(1, LeftDynamicMaterialInstance);
	}
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerBase::ResetFlash() const
{
	RightDynamicMaterialInstance->SetScalarParameterValue(TEXT("EmissiveMultiplier"), 0.f);
	LeftDynamicMaterialInstance->SetScalarParameterValue(TEXT("EmissiveMultiplier"), 0.f);
}

void ATowerBase::Hit()
{
	RightDynamicMaterialInstance->SetScalarParameterValue(TEXT("EmissiveMultiplier"), 200.f);
	LeftDynamicMaterialInstance->SetScalarParameterValue(TEXT("EmissiveMultiplier"), 200.f);
	GetWorldTimerManager().SetTimer(FlashTimerHandle, this, &ATowerBase::ResetFlash, 0.1f, false);
}
