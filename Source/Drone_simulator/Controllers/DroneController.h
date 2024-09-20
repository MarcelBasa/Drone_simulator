#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DroneController.generated.h"

class ADroneHUD;

UCLASS()
class DRONE_SIMULATOR_API ADroneController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void HandleSetPauseMenu();

private:
	ADroneHUD* DroneHUD = nullptr;
};
