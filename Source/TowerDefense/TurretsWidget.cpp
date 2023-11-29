// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretsWidget.h"

#include "TurretPlacement.h"
#include "Components/Button.h"
#include "Components/ListView.h"

void UTurretsWidget::BeginPlay()
{
}

void UTurretsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DeleteButton->OnClicked.AddUniqueDynamic(this, &UTurretsWidget::DeleteTurret);
}

void UTurretsWidget::DeleteTurret()
{
	ATurretPlacement* TurretPlacement = ATurretPlacement::GetInstance();
	TurretPlacement->DeleteDraggableTurret();
}

void UTurretsWidget::TurretSelection() const
{
	ListView->SetVisibility(ESlateVisibility::Hidden);
	DeleteButton->SetVisibility(ESlateVisibility::Visible);
}

void UTurretsWidget::TurretPlaced() const
{
	ListView->SetVisibility(ESlateVisibility::Visible);
	DeleteButton->SetVisibility(ESlateVisibility::Hidden);
}
