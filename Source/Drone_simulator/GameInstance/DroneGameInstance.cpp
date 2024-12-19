#include "DroneGameInstance.h"


void UDroneGameInstance::Init()
{
	Super::Init();

	Reset();
}

FVector* UDroneGameInstance::GetFlyPoint(int32 index)
{
	if (index >= FlyPoints.Num()) return nullptr;

	return &FlyPoints[index];
}

void UDroneGameInstance::Reset()
{
	FilePath = "";
	FlyPoints.Empty();
	DroneFlyHeight = 10000.f;
	DroneFlySpeed = 600.f;
}