#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;
class ADroneController;
class ULidarPointCloudComponent;

UCLASS()
class DRONE_SIMULATOR_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
		UButton* LidarButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CameraButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Quit();
	UFUNCTION()
		void ChooseLidar();
	UFUNCTION()
		void ChooseCamera();

private:
	ADroneController* DroneController = nullptr;

};
