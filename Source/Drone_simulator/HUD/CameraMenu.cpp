#include "CameraMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Components/Button.h"


void UCameraMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &ThisClass::Back);

	DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeUIOnly());
		DroneController->bShowMouseCursor = true;
	}
}

void UCameraMenu::Back()
{
	if (DroneController)
		DroneController->HandleSetMenu();
}