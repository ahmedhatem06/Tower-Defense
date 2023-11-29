// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "TurretUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTurretUpgrade : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	// class UHorizontalBox* UpgradeBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UCanvasPanel* ButtonContainer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* UpgradeButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* SellButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* CloseButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Upgrade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Sell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_TurretType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* HorizontalBox_Rank;

	void StartUpgradeSelection(const int UpgradePrice, const int SellPrice, const int Damage, const int FireRate,
	                           const int Range, const int RankLevel, const EEnemyType TurretType, const bool bRefresh);
	void EndUpgradeSelection() const;

	UFUNCTION()
	void ClickedOnUpgradeButton();
	UFUNCTION()
	void ClickedOnSellButton();
	UFUNCTION()
	void ClickedOnCloseButton();

private:
	void DisplaySellPrice(const int SellPrice) const;
	void DisplayUpgradePrice(const int UpgradePrice) const;
	void DisplayUpgradeCanvas() const;
	void DisplayRankLevel(const int RankLevel) const;
	void DisplayTurretType(EEnemyType TurretType) const;
	void DisplayTurretProperties(const int Damage, const int FireRate, const int Range) const;
	ATurretPlacement* TurretPlacement;
};
