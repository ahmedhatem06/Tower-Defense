// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurretsWidget.generated.h"

class UButton;
class UListView;

UCLASS()
class TOWERDEFENSE_API UTurretsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	 UListView* ListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	 UButton* DeleteButton;

	UFUNCTION()
	void DeleteTurret();

	void TurretSelection() const;
	void TurretPlaced() const;
};
