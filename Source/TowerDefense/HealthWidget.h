// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class AEnemy;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerEnemy(AEnemy* EnemyCharacter) { OwnerEnemy = EnemyCharacter; }

protected:
	//TWeakObjectPtr<AEnemyCharacter> OwnerEnemy;
	TWeakObjectPtr<AEnemy> OwnerEnemy;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
