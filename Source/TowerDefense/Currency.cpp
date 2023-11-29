// Fill out your copyright notice in the Description page of Project Settings.


#include "Currency.h"

#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
//ACurrency* ACurrency::Instance = nullptr;
// Sets default values
ACurrency::ACurrency()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACurrency::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();

	if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ACurrency::StaticClass()); FoundActor->IsA(
		ACurrency::StaticClass()))
	{
		Instance = static_cast<ACurrency*>(FoundActor);
	}
}

// Called every frame
void ACurrency::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACurrency::SpendCurrency(const int Price)
{
	CurrentCurrency -= Price;
	const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->UpdateCurrencyText(CurrentCurrency);
}

void ACurrency::AddCurrency(int Price)
{
	CurrentCurrency += Price;
	const AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->UpdateCurrencyText(CurrentCurrency);
}

int ACurrency::GetCurrency() const
{
	return CurrentCurrency;
}

ACurrency* ACurrency::Instance = nullptr;

// Gets the singleton instance of the ACurrency class.
ACurrency* ACurrency::GetInstance()
{
	return Instance;
}
