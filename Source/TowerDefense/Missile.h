// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Missile.generated.h"

class AEnemy;

UCLASS()
class TOWERDEFENSE_API AMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AEnemy* EnemyCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float RotationSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float MaxTurnRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float InitialSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Properties")
	float MaxSpeed = 2.0f;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MissileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	FVector LaunchDirection;

	void LaunchTowards(const FVector& TargetLocation);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetData(AEnemy* Enemy, float TurretDamage);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
