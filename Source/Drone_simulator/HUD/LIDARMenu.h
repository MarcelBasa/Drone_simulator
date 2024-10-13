#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LIDARMenu.generated.h"

class UButton;
class UTextBlock;
class ADroneController;

UCLASS()
class DRONE_SIMULATOR_API ULIDARMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ChooseFileButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RunMapButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ChosenFileText;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Back();
	UFUNCTION()
		void ChooseFile();
	UFUNCTION()
		void RunMap();

private:
	ADroneController* DroneController;
	FString SelectedFilePath;

	FString OpenFileDialog();

};
