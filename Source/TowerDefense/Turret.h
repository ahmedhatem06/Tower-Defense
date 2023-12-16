// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class AEnergyWeapon;
enum class EEnemyType;
class USphereComponent;
class ABullet;
class UTurretDataAsset;
class ATurretTile;
class ATurretPlacement;
class AEnemy;
class UArrowComponent;
class UNiagaraComponent;

UCLASS()
class TOWERDEFENSE_API ATurret : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int GetPrice();
	int GetUpgradePrice();
	int GetSellPrice();
	virtual void UpgradeTurret();
	void SellTurret();
	int GetRange();
	int GetDamage();
	int GetFireRate();
	int GetRankLevel();
	EEnemyType GetTurretType();
	ATurretTile* GetTurretTile() const;
	bool HasEnemies() const;
	void RangeVisibility(bool Visible);
	void Initialize(ATurretTile* TT);

protected:
	void RotateTurret(float DeltaTime);
	virtual void ShootEnemy(float DeltaTime);
	virtual void ShootAmmo(TSubclassOf<AActor> Projectile);
	virtual void ShootEnergy();
	virtual void ConfigureNiagaraComponents();
	virtual void DeactivateNiagaraComponent();
	virtual void ConfigureSockets();
	void GetTurretData();
	void RemoveEnemy(const AEnemy* Enemy);

	UPROPERTY()
	AEnemy* CurrentEnemyCharacter;

	UPROPERTY()
	AEnergyWeapon* EnergyWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	UTurretDataAsset* TurretDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	TArray<FName> SocketNames;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	TSubclassOf<ABullet> Bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
	TSubclassOf<AMissile> Missile;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* TurretSphereComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* TurretSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretRangeStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TArray<UNiagaraComponent*> NiagaraComponents;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex);


	UFUNCTION()
	void OnTurretClicked(UPrimitiveComponent* pComponent, FKey inKey);

	UPROPERTY()
	TArray<AEnemy*> Enemies;
	float Damage;
	float UpgradeDamage;
	float FireRate;
	float Radius = 500.f;
	float RotationSpeed = 4.f;
	EEnemyType ShootType;
	int Price = 100;
	int UpgradePrice = 150;
	int SellPrice = 50;
	float FireCountdown = 0.f;

private:
	bool IsTurretPlaced = false;
	int RankLevel = 1;

	UPROPERTY()
	ATurretPlacement* TurretPlacement;
	
	UPROPERTY()
	ATurretTile* TurretTile;
};
