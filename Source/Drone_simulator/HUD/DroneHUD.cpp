#include "DroneHUD.h"
#include "Drone_simulator/HUD/PauseMenu.h"


void ADroneHUD::SetPauseMenu()
{
	bIsGamePaused = !bIsGamePaused;
	if (bIsGamePaused)
	{
		DisableInput(GetOwningPlayerController());
		PauseMenuComponent = CreateWidget<UPauseMenu>(GetOwningPlayerController(), PauseMenuClass);
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