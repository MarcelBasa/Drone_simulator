#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;

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
		UButton* OrtofotomapaButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Quit();
	UFUNCTION()
		void ChooseLidar();
	UFUNCTION()
		void ChooseOrtofotomapa();

private:
	APlayerController* PlayerController;
	void LoadMap(FString mapName);
};
