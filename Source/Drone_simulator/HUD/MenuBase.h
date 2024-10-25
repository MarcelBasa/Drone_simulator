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
		UButton* BackButton;

		
protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Back();
	ADroneController* DroneController = nullptr;

};
