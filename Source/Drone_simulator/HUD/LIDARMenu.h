#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "LIDARMenu.generated.h"

class UButton;
class UTextBlock;
class UDroneGameInstance;

UCLASS()
class DRONE_SIMULATOR_API ULIDARMenu : public UMenuBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* ChooseFileButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RunMapButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ChosenFileText;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void ChooseFile();
	UFUNCTION()
		void RunMap();

private:
	UDroneGameInstance* DroneGameInstance = nullptr;
	FString SelectedFilePath;

	FString OpenFileDialog();

};
