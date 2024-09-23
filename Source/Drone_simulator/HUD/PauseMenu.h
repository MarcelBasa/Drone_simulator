#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;
class ADroneController;

UCLASS()
class DRONE_SIMULATOR_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
		void Quit();
	UFUNCTION()
		void Resume();
	UFUNCTION()
		void BackToMenu();

private:
	ADroneController* DroneController = nullptr;
	void SetCursorCenter();
};
