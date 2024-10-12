#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DroneGameMode.generated.h"

UCLASS()
class DRONE_SIMULATOR_API ADroneGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADroneGameMode();

protected:
	virtual void BeginPlay() override;

private:
	void LoadLidarPointCloud(const FString& FilePath);
	FString OpenFileDialog();
};
