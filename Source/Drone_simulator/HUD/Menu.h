#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "Menu.generated.h"

class UButton;

UCLASS()
class DRONE_SIMULATOR_API UMenu : public UMenuBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* LidarButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CameraButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void ChooseLidar();
	UFUNCTION()
		void ChooseCamera();
	void Back() override;

};
