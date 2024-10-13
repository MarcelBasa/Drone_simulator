#include "DroneHUD.h"
#include "Blueprint/UserWidget.h"


void ADroneHUD::SetPauseMenu()
{
	bIsGamePaused = !bIsGamePaused;
	if (bIsGamePaused && PauseMenuClass)
	{
		DisableInput(GetOwningPlayerController());
		PauseMenuComponent = CreateWidget<UUserWidget>(GetOwningPlayerController(), PauseMenuClass);
		PauseMenuComponent->AddToViewport();
	}
	else 
	{
		if (PauseMenuComponent)
		{
			PauseMenuComponent->RemoveFromParent();
			PauseMenuComponent = nullptr;
		}
	}
}

void ADroneHUD::SetLidarMenu()
{
	if (MenuComponent)
		MenuComponent->RemoveFromParent();

	if (LidarMenuClass)
	{
		LidarMenuComponent = CreateWidget<UUserWidget>(GetOwningPlayerController(), LidarMenuClass);
		LidarMenuComponent->AddToViewport();
	}
}

void ADroneHUD::SetMenu()
{
	if (LidarMenuComponent)
		LidarMenuComponent->RemoveFromParent();

	if (MenuClass)
	{
		MenuComponent = CreateWidget<UUserWidget>(GetOwningPlayerController(), MenuClass);
		MenuComponent->AddToViewport();
	}
}