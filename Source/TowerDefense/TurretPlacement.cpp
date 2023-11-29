// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPlacement.h"

#include "Currency.h"
#include "MyHUD.h"
#include "Turret.h"
#include "TurretDataAsset.h"
#include "TurretTile.h"

ATurretPlacement* ATurretPlacement::Instance = nullptr;
// Gets the singleton instance of the ACurrency class.
ATurretPlacement* ATurretPlacement::GetInstance()
{
	return Instance;
}

void ATurretPlacement::EndTurretSelection()
{
	if (CurrentTurret != nullptr)
	{
		CurrentTurret->RangeVisibility(false);
	}
	CurrentTurret = nullptr;
}

void ATurretPlacement::UpgradeTurret()
{
	CurrentTurret->UpgradeTurret();
	Currency->SpendCurrency(CurrentTurret->GetUpgradePrice());
}

void ATurretPlacement::SellTurret()
{
	CurrentTurret->GetTurretTile()->TurretStatus(false);
	CurrentTurret->SellTurret();
	Currency->AddCurrency(CurrentTurret->GetSellPrice());
}

void ATurretPlacement::DeleteDraggableTurret()
{
	TempActor->Destroy();
	TempActor = nullptr;
	MyHUD->TurretPlaced();
	EndTurretSelection();
	IsDragging = false;
}

bool ATurretPlacement::IsPlacingTurret() const
{
	return IsDragging;
}


// Sets default values
ATurretPlacement::ATurretPlacement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurretPlacement::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;
	Currency = ACurrency::GetInstance();
	MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void ATurretPlacement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDragging && TempActor)
	{
		FHitResult Hit;
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(TempActor);
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->GetHitResultUnderCursor(ECC_WorldDynamic, true, Hit);
		FVector NewLocation;
		NewLocation.X = Hit.Location.X;
		NewLocation.Y = Hit.Location.Y;
		NewLocation.Z = 0;
		if (Hit.GetActor() != TempActor)
		{
			TempActor->SetActorLocation(Hit.Location);
		}
	}
}

void ATurretPlacement::LockTurret(const FVector& Location, const bool Locked, ATurretTile* TurretTile)
{
	if (TempActor != nullptr)
	{
		if (Locked)
		{
			IsDragging = false;
			TempActor->SetActorLocation(Location);
			CurrentTurretTile = TurretTile;
		}
		else
		{
			IsDragging = true;
			CurrentTurretTile = nullptr;
		}
	}
}

void ATurretPlacement::PlaceTurretOnTile()
{
	if (!IsDragging && TempActor != nullptr && TempActor->IsA<ATurret>())
	{
		ATurret* CT = Cast<ATurret>(TempActor);
		CT->Initialize(CurrentTurretTile);
		CurrentTurretTile->TurretStatus(true);

		TempActor = nullptr;
		Currency->SpendCurrency(CT->GetPrice());

		MyHUD->TurretPlaced();
	}
}

void ATurretPlacement::SpawnTurret(int TurretIndex)
{
	EndTurretSelection();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Place"));
	const FVector Location(0.0f, 0.0f, 0.0f);
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	TempActor = GetWorld()->SpawnActor<ATurret>(TurretDataAsset[TurretIndex]->GetTurret(), Location, Rotation);
	IsDragging = true;
	MyHUD->EndUpgradeSelection();
	MyHUD->TurretSelection();
}

void ATurretPlacement::StartTurretSelection(ATurret* Turret, const bool bRefresh)
{
	if (CurrentTurret != nullptr)
	{
		CurrentTurret->RangeVisibility(false);
	}
	CurrentTurret = Turret;
	CurrentTurret->RangeVisibility(true);
	MyHUD->StartUpgradeSelection(CurrentTurret->GetUpgradePrice(), CurrentTurret->GetSellPrice(),
	                             CurrentTurret->GetDamage(), CurrentTurret->GetFireRate(), CurrentTurret->GetRange(),
	                             CurrentTurret->GetRankLevel(), CurrentTurret->GetTurretType(), bRefresh);
}
