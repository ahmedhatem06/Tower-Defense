// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class AEnemy;
class UBoxComponent;

UCLASS()
class TOWERDEFENSE_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AEnemy* EnemyCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
	float RotationSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
	float MoveSpeed;

	float Damage;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BulletBoxComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetData(AEnemy* Enemy, float TurretDamage);
};
