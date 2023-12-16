// Fill out your copyright notice in the Description page of Project Settings.


#include "DataWidget.h"

#include "MyHUD.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UDataWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MaxHealth = Health;
}

void UDataWidget::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (UpdateCountdownTimer)
	{
		const int32 IntCountdown = static_cast<int32>(Countdown);
		const FString WaveNumberString = FString::FromInt(IntCountdown);
		Text_WaveCountdown->SetText(FText::FromString(WaveNumberString));
		if (Countdown <= 1)
		{
			UpdateCountdownTimer = false;
			Countdown = 0;
			CountdownHorizontalBox->SetVisibility(ESlateVisibility::Hidden);
		}
		Countdown -= InDeltaTime;
	}
}

void UDataWidget::UpdateWaveText(const int WaveNumber) const
{
	const FString WaveNumberString = FString::FromInt(WaveNumber);
	Text_Wave->SetText(FText::FromString(WaveNumberString));
}

void UDataWidget::WaveCountdown(const float WaveTimer)
{
	UpdateCountdownTimer = true;
	CountdownHorizontalBox->SetVisibility(ESlateVisibility::Visible);
	Countdown = WaveTimer;
}

void UDataWidget::UpdateCurrencyText(const int CurrencyNumber) const
{
	const FString CurrencyNumberString = FString::FromInt(CurrencyNumber);
	Text_Currency->SetText(FText::FromString(CurrencyNumberString));
}

void UDataWidget::ReceiveDamage(const float DamageTaken)
{
	Health -= DamageTaken;
	UpdateHealthBar();

	if (Health <= 0)
	{
		const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		MyHUD->GameOver();
	}
}

FText UDataWidget::GetHealthPercentageText() const
{
	const int32 Percentage = FMath::RoundToInt(GetHealthPercentage() * 100.0f);
	return FText::Format(FText::FromString("{0}%"), FText::AsNumber(Percentage));
}

float UDataWidget::GetHealthPercentage() const
{
	return FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f);
}

void UDataWidget::UpdateHealthBar() const
{
	HealthBar->SetPercent(GetHealthPercentage());
	Text_HealthBarPercentage->SetText(GetHealthPercentageText());
}

void UDataWidget::UpdateAliensText(const int AliensCounter) const
{
	const FString UpgradePriceInFString = FString::FromInt(AliensCounter);
	Text_Aliens->SetText(FText::FromString(UpgradePriceInFString));
}
