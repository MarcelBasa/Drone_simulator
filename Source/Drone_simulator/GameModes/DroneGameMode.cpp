#include "DroneGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LidarPointCloudComponent.h"
#include "LidarPointCloud.h"
#include <windows.h>
#include <commdlg.h>
#include "LidarPointCloudActor.h" 
#include "Blueprint/UserWidget.h"
#include "Drone_simulator/GameInstance/DroneGameInstance.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Drone_simulator/Pawns/Drone.h"


ADroneGameMode::ADroneGameMode() 
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADroneGameMode::BeginPlay()
{
	Super::BeginPlay();

	ADroneController* DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
		DroneController->HandleSetCameraMenu();

	SetLoadingScreen();
	SetMapParameters();
}

void ADroneGameMode::LoadLidarPointCloud(const FString& FilePath)
{
	ULidarPointCloud* LoadedPointCloud = ULidarPointCloud::CreateFromFile(FilePath);

	if (LoadedPointCloud)
	{
		TArray<AActor*> LidarPoints;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALidarPointCloudActor::StaticClass(), LidarPoints);
		if (LidarPoints[0])
		{
			ALidarPointCloudActor* LIDAR = Cast<ALidarPointCloudActor>(LidarPoints[0]);
			if (LIDAR)
			{
				LIDAR->SetPointCloud(LoadedPointCloud);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s "), *FilePath);
	}
}

void ADroneGameMode::SetLoadingScreen()
{
	if (LoadingScreenClass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			LoadingScreenComp = CreateWidget<UUserWidget>(PlayerController, LoadingScreenClass);
			if (LoadingScreenComp)
			{
				LoadingScreenComp->AddToViewport();

				FTimerHandle LoadingScreenTimer;
				GetWorldTimerManager().SetTimer(LoadingScreenTimer, this, &ThisClass::TimerFinish, 6.f);
			}
		}
	}
}

void ADroneGameMode::TimerFinish()
{
	if (LoadingScreenComp)
		LoadingScreenComp->RemoveFromParent();
}

void ADroneGameMode::SetMapParameters()
{
	DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (DroneGameInstance)
		LoadLidarPointCloud(DroneGameInstance->GetFilePath());
}

void ADroneGameMode::StartGame(FVector2D FirstPoint)
{
	if (PlayerPawnClass)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if(DroneGameInstance)
			{
				float DroneFlyHeight = DroneGameInstance->GetDroneFlyHeight();
				FVector SpawnLocation(FirstPoint.X, FirstPoint.Y, DroneFlyHeight);
				FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

				ADrone* SpawnedPawn = GetWorld()->SpawnActor<ADrone>(PlayerPawnClass, SpawnLocation, SpawnRotation);
				if (SpawnedPawn)
				{
					PlayerController->Possess(SpawnedPawn);
					if (DroneGameInstance)
						SpawnedPawn->StartFly(DroneGameInstance->GetFlyPoints(), DroneFlyHeight, DroneGameInstance->GetDroneFlySpeed());
				}
			}
		}
	}
}

void ADroneGameMode::EndGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "D:/UE_5_projekty_D/Drone_simulator/Content/Maps/StartMap");
}


void ADroneGameMode::StartRecording()
{

}

void ADroneGameMode::StopRecording()
{

}