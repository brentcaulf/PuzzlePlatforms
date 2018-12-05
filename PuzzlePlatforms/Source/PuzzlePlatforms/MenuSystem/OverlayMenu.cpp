// Fill out your copyright notice in the Description page of Project Settings.

#include "OverlayMenu.h"

#include "Components/Button.h"

bool UOverlayMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelOverlayMenuButton != nullptr)) return false;
	CancelOverlayMenuButton->OnClicked.AddDynamic(this, &UOverlayMenu::CancelMenu);

	if (!ensure(MainMenuOverlayMenuButton != nullptr)) return false;
	MainMenuOverlayMenuButton->OnClicked.AddDynamic(this, &UOverlayMenu::LoadMainMenu);

	return true;
}

void UOverlayMenu::CancelMenu()
{
	Teardown();
}

void UOverlayMenu::LoadMainMenu()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->LoadMainMenu();
	}
}
