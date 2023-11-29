// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Ground.h"

#include "MyEnemyAIController.h"
#include "MyHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

class AMyEnemyAIController;

void AEnemy_Ground::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();
	MyEnemyController = GetController<AMyEnemyAIController>();
	MyEnemyController->MoveEnemy(TargetLocation);

	AttackTimerDelegate.BindUFunction(this, FName("DamageBase"));
}

void AEnemy_Ground::Dead()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	HealthWidgetComponent->SetVisibility(false);
	CharacterMovementComponent->MaxWalkSpeed = 0;
	CharacterMovementComponent->bUseRVOAvoidance = false;
	if (UCapsuleComponent* EnemyCapsuleComponent = GetCapsuleComponent())
	{
		// Set the capsule component's collision to "No Collision"
		EnemyCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	EnemyDead();
}

void AEnemy_Ground::Arrived()
{
	SetActorTickEnabled(false);

	if (UCapsuleComponent* ECapsuleComponent = GetCapsuleComponent())
	{
		ECapsuleComponent->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	}

	StartAttackingBase();

	SetActorRotation(FRotator(0.f, 90.f, 0.f));
	CharacterMovementComponent->bUseRVOAvoidance = false;
	// Set the timer to loop every 2 seconds
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, 2.62f, true, DamageRate);
}
