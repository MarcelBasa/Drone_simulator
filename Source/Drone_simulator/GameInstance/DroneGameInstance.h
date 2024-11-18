#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DroneGameInstance.generated.h"


UCLASS()
class DRONE_SIMULATOR_API UDroneGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	FString FilePath = "";
	TArray<FVector2D> FlyPoints;
	float DroneFlyHeight = 8800.0f;
	float DroneFlySpeed = 600.0f;

protected:
	void Init();

public:
	inline void SetFilePath(FString& newFilePath) { FilePath = newFilePath; }
	inline void SetDroneFlyHeight(float newHeight) { DroneFlyHeight = newHeight; }
	inline void SetDroneFlySpeed(float newSpeed) { DroneFlySpeed = newSpeed; }
	inline void AddPointFly(FVector2D newPoint) { FlyPoints.Add(newPoint); }

	inline FString GetFilePath() const { return FilePath; }
	inline float GetDroneFlyHeight() const { return DroneFlyHeight; }
	inline float GetDroneFlySpeed() const { return DroneFlySpeed; }
	inline TArray<FVector2D> GetFlyPoints() const { return FlyPoints; }
};
