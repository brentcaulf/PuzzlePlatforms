// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	// constructor
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);

	// initialization
	virtual void Init();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	UFUNCTION(Exec)
	void LoadMainMenu() override;

	UFUNCTION()
	void ExitGame() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadOverlayMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;	
	TSubclassOf<class UUserWidget> OverlayClass;

	class UMainMenu* Menu;
	class UOverlayMenu* Overlay;
};
