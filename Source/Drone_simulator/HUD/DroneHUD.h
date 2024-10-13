#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DroneHUD.generated.h"

class UUserWidget;

UCLASS()
class DRONE_SIMULATOR_API ADroneHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void SetPauseMenu();
	void SetLidarMenu();
	void SetMenu();

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PauseMenuClass;
	UUserWidget* PauseMenuComponent = nullptr;
	bool bIsGamePaused = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MenuClass;
	UUserWidget* MenuComponent = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LidarMenuClass;
	UUserWidget* LidarMenuComponent = nullptr;
};
