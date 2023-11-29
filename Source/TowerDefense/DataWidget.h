// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataWidget.generated.h"

class UHorizontalBox;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UDataWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void UpdateCurrencyText(int CurrencyNumber) const;
	void UpdateWaveText(int WaveNumber) const;
	void WaveCountdown(float WaveTimer);
	void ReceiveDamage(float DamageTaken);
	void UpdateAliensText(const int AliensCounter) const;

protected:
	bool UpdateCountdownTimer = false;
	float Countdown = 0.f;
	float MaxHealth = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties", meta=(AllowPrivateAccess="true"))
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_HealthBarPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Currency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_WaveCountdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* CountdownHorizontalBox;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> HealthWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Aliens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthPoints;

	FText GetHealthPercentageText() const;
	float GetHealthPercentage() const;
	void UpdateHealthBar() const;
};
