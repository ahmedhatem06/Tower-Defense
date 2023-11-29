// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include "Enemy.h"
#include "Components/ProgressBar.h"

void UHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(!OwnerEnemy.IsValid())
	{
		return;
	}
	HealthBar->SetPercent(OwnerEnemy->GetHealth() / OwnerEnemy->GetMaxHealth());
}