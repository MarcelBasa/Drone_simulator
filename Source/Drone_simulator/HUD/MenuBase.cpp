#include "MenuBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"


void UMenuBase::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this, &ThisClass::Exit);

	DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeUIOnly());
		DroneController->bShowMouseCursor = true;
	}
}

void UMenuBase::Exit()
{
	if (DroneController)
		DroneController->ConsoleCommand("quit");
}