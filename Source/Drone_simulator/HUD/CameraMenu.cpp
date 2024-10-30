#include "CameraMenu.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Drone_simulator/GameInstance/DroneGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpinBox.h"

void UCameraMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChooseFlyHeightButton)
	{
		ChooseFlyHeightButton->OnValueChanged.AddDynamic(this, &ThisClass::OnFlyHeightChanged);
	}
	DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (DroneGameInstance)
		ChooseFlyHeightButton->SetValue(DroneGameInstance->GetDroneFlyHeight());
}

void UCameraMenu::OnFlyHeightChanged(float NewValue)
{
	if (DroneGameInstance)
		DroneGameInstance->SetDroneFlyHeight(NewValue);
}