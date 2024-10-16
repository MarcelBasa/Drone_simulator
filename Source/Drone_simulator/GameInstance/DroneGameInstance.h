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

protected:
	void Init();

public:
	inline void SetFilePath(FString& NewFilePath) { FilePath = NewFilePath; }
	FString GetFilePath() const { return FilePath; }
};
