#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "CameraMenu.generated.h"

class USpinBox;
class UDroneGameInstance;
class UImage;
class UButton;

UCLASS()
class DRONE_SIMULATOR_API UCameraMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		USpinBox* ChooseFlyHeightSpinBox;
	UPROPERTY(meta = (BindWidget))
		USpinBox* ChooseFlySpeedSpinBox;
	UPROPERTY(meta = (BindWidget))
		UImage* MapArea;
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnFlyHeightChanged(float NewValue);
	UFUNCTION()
		void OnFlySpeedChanged(float NewValue);
	UFUNCTION()
		void OnStartGameButtonClick();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UDroneGameInstance* DroneGameInstance = nullptr;
	UPROPERTY(Editanywhere)
		TSubclassOf<UUserWidget> DotWidgetClass;	
	UPROPERTY(Editanywhere)
		float DotSize = 40;
};
