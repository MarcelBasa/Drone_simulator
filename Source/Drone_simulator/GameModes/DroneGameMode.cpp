#include "DroneGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LidarPointCloudComponent.h"
#include "LidarPointCloud.h"
#include <windows.h>
#include <commdlg.h>
#include "LidarPointCloudActor.h" 
#include "Blueprint/UserWidget.h"


ADroneGameMode::ADroneGameMode() 
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADroneGameMode::BeginPlay()
{
	Super::BeginPlay();

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