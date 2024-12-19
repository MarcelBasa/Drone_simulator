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
	TArray<FVector> FlyPoints;
	float DroneFlyHeight = 10000.f;
	float DroneFlySpeed = 600.f;

protected:
	void Init();

public:
	inline void SetFilePath(FString& newFilePath) { FilePath = newFilePath; }
	inline void SetDroneFlyHeight(float newHeight) { DroneFlyHeight = newHeight; }
	inline void SetDroneFlySpeed(float newSpeed) { DroneFlySpeed = newSpeed; }
	inline void AddPointFly(double X, double Y) { FlyPoints.Add(FVector(X, Y, DroneFlyHeight)); }

	inline FString GetFilePath() const { return FilePath; }
	inline float GetDroneFlyHeight() const { return DroneFlyHeight; }
	inline float GetDroneFlySpeed() const { return DroneFlySpeed; }
	inline TArray<FVector> GetFlyPoints() const { return FlyPoints; }

	void Reset();
	FVector* GetFlyPoint(int32 index);
};
