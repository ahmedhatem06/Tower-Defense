// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "EnemiesManager.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PauseImage->OnMouseButtonDownEvent.BindUFunction(this, "ClickedOnPauseImage");
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ClickedOnResumeButton);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::UPauseMenu::ClickedOnQuitButton);
	RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::UPauseMenu::ClickedOnRestartButton);

	QuitButton_GO->OnClicked.AddDynamic(this, &UPauseMenu::UPauseMenu::ClickedOnQuitButton);
	RestartButton_GO->OnClicked.AddDynamic(this, &UPauseMenu::UPauseMenu::ClickedOnRestartButton);
	StartButton->OnClicked.AddDynamic(this, &UPauseMenu::StartGame);
}

void UPauseMenu::UpdateAliensText(UTextBlock* AliensText, const int AliensCounter) const
{
	const FString UpgradePriceInFString = FString::FromInt(AliensCounter);
	AliensText->SetText(FText::FromString(UpgradePriceInFString));
}

void UPauseMenu::ClickedOnPauseImage()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->SetPause(true);
	}

	const AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
	UpdateAliensText(Text_Aliens, EnemiesManager->GetAliensKilled());

	PauseMenuCanvas->SetVisibility((ESlateVisibility::Visible));
}

void UPauseMenu::ClickedOnResumeButton()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->SetPause(false);
	}
	PauseMenuCanvas->SetVisibility((ESlateVisibility::Hidden));
}

void UPauseMenu::ClickedOnRestartButton()
{
	if (const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld()); !CurrentLevelName.IsEmpty())
	{
		UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);
	}
}

void UPauseMenu::ClickedOnQuitButton()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}

void UPauseMenu::StartGame()
{
	StartButton->SetVisibility(ESlateVisibility::Hidden);
	AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
	EnemiesManager->StartWave();
}

void UPauseMenu::GameOver() const
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->SetPause(true);
	}

	const AEnemiesManager* EnemiesManager = AEnemiesManager::GetInstance();
	UpdateAliensText(Text_Aliens_GO, EnemiesManager->GetAliensKilled());

	GameOverCanvas->SetVisibility((ESlateVisibility::Visible));
}
