// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "OverlayMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UOverlayMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void CancelMenu();
	UFUNCTION()
	void LoadMainMenu();
	UFUNCTION()
	void ExitGame();

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelOverlayMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuOverlayMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitOverlayMenuButton;
};
