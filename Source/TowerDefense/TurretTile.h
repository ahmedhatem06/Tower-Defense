// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretTile.generated.h"

class ATurretPlacement;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class TOWERDEFENSE_API ATurretTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretTile();
	virtual void Tick(float DeltaTime) override;
	void TurretStatus(bool Status);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION()
	void OnBoxBeginCursorOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnBoxEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category="Tile Materials")
	UMaterial* GreenMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Tile Materials")
	UMaterial* BlueMaterial;

	UPROPERTY()
	ATurretPlacement* TurretPlacement;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ChangeTileMaterial(UMaterial* Material) const;

	bool HasTurret = false;
};
