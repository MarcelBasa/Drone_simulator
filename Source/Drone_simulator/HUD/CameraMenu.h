#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "CameraMenu.generated.h"

class USpinBox;
class UDroneGameInstance;

UCLASS()
class DRONE_SIMULATOR_API UCameraMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		USpinBox* ChooseFlyHeightButton;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnFlyHeightChanged(float NewValue);

private:
	UDroneGameInstance* DroneGameInstance = nullptr;

	
};
