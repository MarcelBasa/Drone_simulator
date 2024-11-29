#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DroneGameMode.generated.h"

class UUserWidget;
class UDroneGameInstance;

UCLASS()
class DRONE_SIMULATOR_API ADroneGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADroneGameMode();
	void LoadLidarPointCloud(const FString& FilePath);
	void StartGame(FVector2D FirstPoint);
	void EndGame();

protected:
	virtual void BeginPlay() override;    
	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> PlayerPawnClass;

private:
	UPROPERTY(Editanywhere)
		TSubclassOf<UUserWidget> LoadingScreenClass;
	UUserWidget* LoadingScreenComp;
	UDroneGameInstance* DroneGameInstance;

	void TimerFinish();
	void SetLoadingScreen();
	void SetMapParameters();

	void StartRecording();
	void StopRecording();

};
