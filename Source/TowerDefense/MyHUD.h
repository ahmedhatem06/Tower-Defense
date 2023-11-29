// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataWidget.h"
#include "PauseMenu.h"
#include "Turret.h"
#include "TurretsWidget.h"


#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AMyHUD : public AHUD
{
	AMyHUD();
	GENERATED_BODY()

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> MyNewWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> MyUpgradeWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> MyDataWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UPauseMenu> MyPauseMenuWidget;

public:
	void TurretSelection() const;
	void TurretPlaced() const;
	void StartUpgradeSelection(const int UpgradePrice, const int SellPrice, const int Damage, const int FireRate,
	                           const int Range, const int RankLevel, const EEnemyType TurretType,
	                           const bool bRefresh) const;
	void EndUpgradeSelection() const;

	void UpdateWaveText(int WaveNumber) const;
	void WaveCountdown(float WaveTimer) const;
	void UpdateCurrencyText(int CurrencyNumber) const;
	void ReceiveDamage(float DamageTaken) const;
	void AlienDead(int AliensKilled) const;
	void GameOver() const;

private:
	UTurretsWidget* TurretsWidget;
	class UTurretUpgrade* UpgradeWidget;
	UDataWidget* DataWidget;
	UPauseMenu* PauseMenuWidget;
};
