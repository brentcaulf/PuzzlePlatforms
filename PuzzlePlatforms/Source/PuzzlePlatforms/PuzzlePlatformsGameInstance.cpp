// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/OverlayMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> OverlayBPClass(TEXT("/Game/MenuSystem/WBP_OverlayMenu"));
	if (!ensure(OverlayBPClass.Class != nullptr)) return;

	OverlayClass = OverlayBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *OverlayClass->GetName());
}

void UPuzzlePlatformsGameInstance::Host()
{
	// Commented out since the TearDown function was replaced in the MainMenu with OnLevelRemovedFromWorld
	/*if (Menu != nullptr)
	{
		Menu->Teardown();
	}*/
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/PuzzlePlatforms?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString & Address)
{
	// Commented out since the TearDown function was replaced in the MainMenu with OnLevelRemovedFromWorld
	/*if (Menu != nullptr)
	{
		Menu->Teardown();
	}*/
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);	
}

void UPuzzlePlatformsGameInstance::ExitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadOverlayMenu()
{
	if (!ensure(OverlayClass != nullptr)) return;

	Overlay = CreateWidget<UOverlayMenu>(this, OverlayClass);
	if (!ensure(Overlay != nullptr)) return;

	Overlay->Setup();

	Overlay->SetMenuInterface(this);
}
