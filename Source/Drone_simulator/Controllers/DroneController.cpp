#include "DroneController.h"
#include "Drone_simulator/HUD/DroneHUD.h"


void ADroneController::HandleSetPauseMenu()
{
	DroneHUD = DroneHUD == nullptr ? Cast<ADroneHUD>(GetHUD()) : DroneHUD;
	if (DroneHUD)
		DroneHUD->SetPauseMenu();
}

void ADroneController::HandleSetLidarMenu()
{
	DroneHUD = DroneHUD == nullptr ? Cast<ADroneHUD>(GetHUD()) : DroneHUD;
	if (DroneHUD)
		DroneHUD->SetLidarMenu();
}

void ADroneController::HandleSetCameraMenu()
{
	DroneHUD = DroneHUD == nullptr ? Cast<ADroneHUD>(GetHUD()) : DroneHUD;
	if (DroneHUD)
		DroneHUD->SetCameraMenu();
}
