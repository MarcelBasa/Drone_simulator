#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

class UCanvasPanel;
class UButton;
class ADroneController;

UCLASS()
class DRONE_SIMULATOR_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* Background;
	UPROPERTY(meta = (BindWidget))
		UButton* ExitButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		virtual void Exit();
	ADroneController* DroneController = nullptr;

};
