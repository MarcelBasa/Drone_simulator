#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DroneHUD.generated.h"

class UPauseMenu;

UCLASS()
class DRONE_SIMULATOR_API ADroneHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void SetPauseMenu();

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UPauseMenu> PauseMenuClass;
	UPauseMenu* PauseMenuComponent = nullptr;
	bool bIsGamePaused = false;
};
