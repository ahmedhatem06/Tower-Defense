// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Currency.h"
#include "TurretUpgrade.h"

AMyHUD::AMyHUD()
{
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MyNewWidgetClass)
	{
		TurretsWidget = CreateWidget<UTurretsWidget>(GetWorld(), MyNewWidgetClass);

		if (TurretsWidget)
		{
			TurretsWidget->AddToViewport();
		}

		UpgradeWidget = CreateWidget<UTurretUpgrade>(GetWorld(), MyUpgradeWidget);

		if (UpgradeWidget)
		{
			UpgradeWidget->AddToViewport();
			UpgradeWidget->EndUpgradeSelection();
		}

		DataWidget = CreateWidget<UDataWidget>(GetWorld(), MyDataWidget);

		if (DataWidget)
		{
			DataWidget->AddToViewport();
			const ACurrency* Currency = ACurrency::GetInstance();
			DataWidget->UpdateCurrencyText(Currency->GetCurrency());
		}

		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(), MyPauseMenuWidget);

		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
		}
	}
}

void AMyHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyHUD::TurretSelection() const
{
	TurretsWidget->TurretSelection();
}

void AMyHUD::TurretPlaced() const
{
	TurretsWidget->TurretPlaced();
}

void AMyHUD::StartUpgradeSelection(const int UpgradePrice, const int SellPrice, const int Damage, const int FireRate,
                                   const int Range, const int RankLevel, const EEnemyType TurretType,
                                   const bool bRefresh) const
{
	UpgradeWidget->StartUpgradeSelection(UpgradePrice, SellPrice, Damage, FireRate, Range, RankLevel, TurretType,
	                                     bRefresh);
}

void AMyHUD::EndUpgradeSelection() const
{
	UpgradeWidget->EndUpgradeSelection();
}

void AMyHUD::UpdateWaveText(const int WaveNumber) const
{
	DataWidget->UpdateWaveText(WaveNumber);
}

void AMyHUD::WaveCountdown(const float WaveTimer) const
{
	DataWidget->WaveCountdown(WaveTimer);
}

void AMyHUD::UpdateCurrencyText(const int CurrencyNumber) const
{
	DataWidget->UpdateCurrencyText(CurrencyNumber);
}

void AMyHUD::ReceiveDamage(const float DamageTaken) const
{
	DataWidget->ReceiveDamage(DamageTaken);
}

void AMyHUD::AlienDead(const int AliensKilled) const
{
	DataWidget->UpdateAliensText(AliensKilled);
}

void AMyHUD::GameOver() const
{
	PauseMenuWidget->GameOver();
}
