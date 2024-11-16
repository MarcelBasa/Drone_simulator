#include "StartGameMode.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Kismet/GameplayStatics.h"


void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	ADroneController* DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
		DroneController->HandleSetLidarMenu();
}