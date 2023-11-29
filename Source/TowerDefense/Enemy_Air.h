// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Enemy_Air.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemy_Air : public AEnemy
{
	GENERATED_BODY()
	AEnemy_Air();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Dead() override;
	FVector CurrentLocation;
	float RotationSpeed = 0;
	void Explode();
	void DestroyAirEnemy();

	UPROPERTY()
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY()
	UCapsuleComponent* EnemyCapsuleComponent;

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMesh;
};
