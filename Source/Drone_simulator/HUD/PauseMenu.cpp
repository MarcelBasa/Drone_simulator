#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &ThisClass::Quit);
	ResumeButton->OnClicked.AddDynamic(this, &ThisClass::Resume);

	DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeGameAndUI());
		DroneController->bShowMouseCursor = true;
		SetCursorCenter();
	}
}

void UPauseMenu::NativeDestruct()
{
	Super::NativeDestruct();

	if(DroneController)
	{ 
		DroneController->SetInputMode(FInputModeGameOnly());
		DroneController->bShowMouseCursor = false;
	}
}

void UPauseMenu::Quit()
{
	if (DroneController)
		DroneController->ConsoleCommand("quit");
}

void UPauseMenu::Resume()
{
	if (DroneController)
		DroneController->HandleSetPauseMenu();
}

void UPauseMenu::SetCursorCenter()
{
	if (DroneController)
	{
		const ULocalPlayer* LocalPlayer = DroneController->GetLocalPlayer();
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		if (Viewport)
		{
			FVector2D ViewportSize;
			LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
			const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
			const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);
			Viewport->SetMouse(X, Y);
		}
	}
}