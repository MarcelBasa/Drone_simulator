#include "Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"


void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &ThisClass::Quit);
	LidarButton->OnClicked.AddDynamic(this, &ThisClass::ChooseLidar);
	CameraButton->OnClicked.AddDynamic(this, &ThisClass::ChooseCamera);

	DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeUIOnly());
		DroneController->bShowMouseCursor = true;
	}
}

void UMenu::Quit()
{
	if (DroneController)
		DroneController->ConsoleCommand("quit");
}

void UMenu::ChooseLidar()
{
	if (DroneController)
		DroneController->HandleSetLidarMenu();
}

void UMenu::ChooseCamera()
{
	if (DroneController)
		DroneController->HandleSetCameraMenu();
}
