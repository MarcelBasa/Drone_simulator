#include "Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"


void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	LidarButton->OnClicked.AddDynamic(this, &ThisClass::ChooseLidar);
	CameraButton->OnClicked.AddDynamic(this, &ThisClass::ChooseCamera);
}

void UMenu::Back()
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
