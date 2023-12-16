// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UEnemyDataAsset;
class UWidgetComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum class EEnemyType
{
	Ground UMETA(DisplayName = "Ground"),
	Air UMETA(DisplayName = "Air")
};

UCLASS()
class TOWERDEFENSE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	float GetHealth() const;
	void SetHealth(float Val);

	float GetMaxHealth() const;
	void SetMaxHealth(float Val);
	EEnemyType GetEnemyType() const;
	void ReceiveDamage(float Val);
	void CheckHealth();

	bool IsDead() const;

	void TakeSlow(float SlowerSpeed);

	void ResetSpeed();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetEnemyData();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* MissileArrowComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComponent;

	bool bIsDead = false;

	virtual void Dead();

	void DestroyEnemyCharacter();

	UFUNCTION()
	void DamageBase() const;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAIProperties")
	UEnemyDataAsset* EnemyDataAsset;

	FVector TargetLocation;
	float Damage;
	float Speed;
	float Health;
	float MaxHealth;
	int Price;
	int MinSpeed;
	float StartSpeed = 0.f;
	float DamageRate = 0.f;
	EEnemyType EnemyTpe;
};
