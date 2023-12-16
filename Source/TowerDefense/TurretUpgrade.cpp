// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretUpgrade.h"

#include "Enemy.h"
#include "TurretPlacement.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UTurretUpgrade::DisplaySellPrice(const int SellPrice) const
{
	const FString SellPriceInFString = FString::FromInt(SellPrice);
	Text_Sell->SetText(FText::FromString(SellPriceInFString));
}

void UTurretUpgrade::DisplayUpgradePrice(const int UpgradePrice) const
{
	const FString UpgradePriceInFString = FString::FromInt(UpgradePrice);
	Text_Upgrade->SetText(FText::FromString(UpgradePriceInFString));
}

void UTurretUpgrade::DisplayUpgradeCanvas() const
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);
	FWidgetTransform Transform;
	Transform.Translation.X = MouseX;
	Transform.Translation.Y = MouseY - 200.f;
	ButtonContainer->SetRenderTransform(Transform);
	ButtonContainer->SetVisibility(ESlateVisibility::Visible);
}

void UTurretUpgrade::DisplayRankLevel(const int RankLevel) const
{
	if (RankLevel >= 3)
	{
		UpgradeButton->SetIsEnabled(false);
	}
	else
	{
		UpgradeButton->SetIsEnabled(true);
	}
	int CurrentChild = 1;
	for (UWidget* Child : HorizontalBox_Rank->GetAllChildren())
	{
		if (CurrentChild <= RankLevel)
		{
			if (UImage* ImageChild = Cast<UImage>(Child))
			{
				// Assuming the child is an image, you can change its visibility here
				ImageChild->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (UImage* ImageChild = Cast<UImage>(Child))
			{
				// Assuming the child is an image, you can change its visibility here
				ImageChild->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		CurrentChild++;
	}
}

void UTurretUpgrade::DisplayTurretType(const EEnemyType TurretType) const
{
	FString PropertyInFString = "A";

	switch (TurretType)
	{
	case EEnemyType::Ground:
		PropertyInFString = "ANTI-GROUND";
		break;

	case EEnemyType::Air:
		PropertyInFString = "ANTI-AIR";
		break;
	}

	Text_TurretType->SetText(FText::FromString(PropertyInFString));
}

void UTurretUpgrade::DisplayTurretProperties(const int Damage, const int FireRate, const int Range) const
{
	FString PropertyInFString = FString::FromInt(Damage);
	Text_Damage->SetText(FText::FromString(PropertyInFString));

	PropertyInFString = FString::FromInt(FireRate);
	Text_FireRate->SetText(FText::FromString(PropertyInFString));

	PropertyInFString = FString::FromInt(Range);
	Text_Range->SetText(FText::FromString(PropertyInFString));
}

void UTurretUpgrade::NativeConstruct()
{
	Super::NativeConstruct();

	UpgradeButton->OnClicked.AddUniqueDynamic(this, &UTurretUpgrade::ClickedOnUpgradeButton);
	SellButton->OnClicked.AddUniqueDynamic(this, &UTurretUpgrade::ClickedOnSellButton);
	CloseButton->OnClicked.AddUniqueDynamic(this, &UTurretUpgrade::UTurretUpgrade::ClickedOnCloseButton);

	TurretPlacement = ATurretPlacement::GetInstance();
}

void UTurretUpgrade::StartUpgradeSelection(const int UpgradePrice, const int SellPrice, const int Damage,
                                           const int FireRate, const int Range, const int RankLevel,
                                           const EEnemyType TurretType, const bool bRefresh)
{
	DisplayUpgradePrice(UpgradePrice);
	DisplaySellPrice(SellPrice);
	DisplayTurretProperties(Damage, FireRate, Range);
	DisplayRankLevel(RankLevel);
	DisplayTurretType(TurretType);
	if (!bRefresh)
	{
		DisplayUpgradeCanvas();
	}
}

void UTurretUpgrade::EndUpgradeSelection() const
{
	//UpgradeBox->SetVisibility(ESlateVisibility::Hidden);
	ButtonContainer->SetVisibility(ESlateVisibility::Hidden);
}

void UTurretUpgrade::ClickedOnUpgradeButton()
{
	TurretPlacement->UpgradeTurret();
}

void UTurretUpgrade::ClickedOnSellButton()
{
	TurretPlacement->SellTurret();
	TurretPlacement->EndTurretSelection();
	EndUpgradeSelection();
}

void UTurretUpgrade::ClickedOnCloseButton()
{
	TurretPlacement->EndTurretSelection();
	EndUpgradeSelection();
}
