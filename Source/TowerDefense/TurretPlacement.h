// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretPlacement.generated.h"

class ATurret;
class UTurretDataAsset;
class ATurretTile;
class ACurrency;
class AMyHUD;

UCLASS()
class TOWERDEFENSE_API ATurretPlacement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretPlacement();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	bool IsDragging = false;

	UPROPERTY()
	AActor* TempActor;

	UPROPERTY()
	ATurret* CurrentTurret;

private:
	static ATurretPlacement* Instance;

	UPROPERTY()
	AMyHUD* MyHUD;

	UPROPERTY()
	ACurrency* Currency;

	UPROPERTY()
	ATurretTile* CurrentTurretTile;

public:
	void LockTurret(const FVector& Location, bool Locked, ATurretTile* TurretTile);

	void PlaceTurretOnTile();

	UFUNCTION(BlueprintCallable)
	void SpawnTurret(int TurretIndex);

	void StartTurretSelection(ATurret* Turret, const bool bRefresh);
	void EndTurretSelection();

	static ATurretPlacement* GetInstance();

	void UpgradeTurret();
	void SellTurret();
	bool IsPlacingTurret() const;
	void DeleteDraggableTurret();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Turret Properties")
	TArray<UTurretDataAsset*> TurretDataAsset;
};
