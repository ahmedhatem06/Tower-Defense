// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftStaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Material Properties")
	UMaterialInterface* OriginalMaterial;

	UPROPERTY(EditAnywhere, Category = "Material Properties")
	UMaterialInstanceDynamic* RightDynamicMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Material Properties")
	UMaterialInstanceDynamic* LeftDynamicMaterialInstance;

	void ResetFlash() const;

	FTimerHandle FlashTimerHandle;

public:
	ATowerBase();
	void Hit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
