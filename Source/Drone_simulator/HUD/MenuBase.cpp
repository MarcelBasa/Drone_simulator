#include "MenuBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"


void UMenuBase::NativeConstruct()
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

void UMenuBase::Back()
{
	if (DroneController)
		DroneController->HandleSetMenu();
}