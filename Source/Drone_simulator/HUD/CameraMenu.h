#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CameraMenu.generated.h"

class UButton;
class ADroneController;

UCLASS()
class DRONE_SIMULATOR_API UCameraMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Back();

private:
	ADroneController* DroneController = nullptr;
};
