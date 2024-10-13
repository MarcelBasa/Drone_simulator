#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DroneGameMode.generated.h"

class UUserWidget;

UCLASS()
class DRONE_SIMULATOR_API ADroneGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADroneGameMode();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(Editanywhere)
		TSubclassOf<UUserWidget> LoadingScreenClass;
	UUserWidget* LoadingScreenComp;

	void LoadLidarPointCloud(const FString& FilePath);
	FString OpenFileDialog();
	void TimerFinish();

};
