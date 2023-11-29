// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Currency.h"
#include "EnemiesManager.h"
#include "EnemyDataAsset.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthWidget.h"
#include "MyHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	MissileArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MissileArrowComponent"));
	MissileArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

float AEnemy::GetHealth() const
{
	return Health;
}

void AEnemy::SetHealth(const float Val)
{
	Health = Val;
}

float AEnemy::GetMaxHealth() const
{
	return MaxHealth;
}

void AEnemy::SetMaxHealth(const float Val)
{
	MaxHealth = Val;
}

EEnemyType AEnemy::GetEnemyType() const
{
	return EnemyTpe;
}

void AEnemy::TakeDamage(const float Val)
{
	Health -= Val;

	CheckHealth();
}

void AEnemy::CheckHealth()
{
	if (Health <= 0)
	{
		bIsDead = true;
		//if (!bIsDead)
		//{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Dead"));
		//bIsDead = true;

		ACurrency* Currency = ACurrency::GetInstance();
		Currency->AddCurrency(Price);

		const AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
		EnemiesManager->OnEnemyDestroyEvent.Broadcast(false);

		Dead();
		//}
	}
}

bool AEnemy::IsDead() const
{
	return bIsDead;
}

void AEnemy::Dead()
{
}

void AEnemy::TakeSlow(float SlowerSpeed)
{
	if (CharacterMovementComponent->MaxWalkSpeed <= MinSpeed)
	{
		return;
	}
	Speed -= SlowerSpeed;
	CharacterMovementComponent->MaxWalkSpeed = Speed;
}

void AEnemy::ResetSpeed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Reset Speed"));
	Speed = StartSpeed;
	CharacterMovementComponent->MaxWalkSpeed = StartSpeed;
}

void AEnemy::DestroyEnemyCharacter()
{
	Destroy();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetEnemyData();

	CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->MaxWalkSpeed = Speed;

	UHealthWidget* HealthWidget = Cast<UHealthWidget>(HealthWidgetComponent->GetUserWidgetObject());
	HealthWidget->SetOwnerEnemy(this);

	StartSpeed = CharacterMovementComponent->MaxWalkSpeed;
}


// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Get the character's current velocity
	const FVector CharacterVelocity = GetCharacterMovement()->Velocity;

	// Calculate the rotation to face the direction of movement
	const FRotator NewRotation = CharacterVelocity.ToOrientationRotator();

	// Set the character's rotation to the new rotation
	SetActorRotation(NewRotation);
}

void AEnemy::DamageBase() const
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Attack Base"));
	const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->ReceiveDamage(Damage);
	const AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
	EnemiesManager->TowerBase->Hit();
}

void AEnemy::GetEnemyData()
{
	TargetLocation = EnemyDataAsset->GetTargetLocation();
	Damage = EnemyDataAsset->GetDamage();
	Speed = EnemyDataAsset->GetSpeed();
	Health = EnemyDataAsset->GetHealth();
	MaxHealth = EnemyDataAsset->GetMaxHealth();
	Price = EnemyDataAsset->GetPrice();
	MinSpeed = EnemyDataAsset->GetMinSpeed();
	StartSpeed = EnemyDataAsset->GetStartSpeed();
	DamageRate = EnemyDataAsset->GetDamageRate();
	EnemyTpe = EnemyDataAsset->GetEnemyType();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
