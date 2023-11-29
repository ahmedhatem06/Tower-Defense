// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Currency.generated.h"

UCLASS()
class TOWERDEFENSE_API ACurrency : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACurrency();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Currency")
	int CurrentCurrency;

	void SpendCurrency(int Price);

	void AddCurrency(int Price);

	int GetCurrency() const;

	static ACurrency* GetInstance();

private:
	static ACurrency* Instance;
};
