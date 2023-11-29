// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

public:
	void GameOver() const;

protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* PauseMenuCanvas;

	UPROPERTY(meta=(BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta=(BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Aliens;

	UPROPERTY(meta=(BindWidget))
	UImage* PauseImage;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* GameOverCanvas;

	UPROPERTY(meta=(BindWidget))
	UButton* RestartButton_GO;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton_GO;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Aliens_GO;

	UPROPERTY(meta=(BindWidget))
	UButton* StartButton;

	void UpdateAliensText(UTextBlock* AliensText, const int AliensCounter) const;

	UFUNCTION()
	void ClickedOnPauseImage();
	UFUNCTION()
	void ClickedOnResumeButton();
	UFUNCTION()
	void ClickedOnRestartButton();
	UFUNCTION()
	void ClickedOnQuitButton();
	UFUNCTION()
	void StartGame();
};
