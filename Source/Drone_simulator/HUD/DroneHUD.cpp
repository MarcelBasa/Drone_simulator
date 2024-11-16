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
	if (CameraMenuComponent)
	{
		CameraMenuComponent->RemoveFromParent();
		CameraMenuComponent = nullptr;
	}

	if (LidarMenuClass)
	{
		LidarMenuComponent = CreateWidget<UUserWidget>(GetOwningPlayerController(), LidarMenuClass);
		LidarMenuComponent->AddToViewport();
	}
}

void ADroneHUD::SetCameraMenu()
{
	if (LidarMenuComponent)
	{
		LidarMenuComponent->RemoveFromParent();
		LidarMenuComponent = nullptr;
	}

	if (CameraMenuClass)
	{
		CameraMenuComponent = CreateWidget<UUserWidget>(GetOwningPlayerController(), CameraMenuClass);
		CameraMenuComponent->AddToViewport();
	}
}
