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

	FString SelectedFilePath = OpenFileDialog();
	if (!SelectedFilePath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Wybrany plik: %s"), *SelectedFilePath);
		LoadLidarPointCloud(SelectedFilePath);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Nie wybrano pliku."));
	}
}

void ADroneGameMode::TimerFinish()
{
	if (LoadingScreenComp)
		LoadingScreenComp->RemoveFromParent();
}

FString ADroneGameMode::OpenFileDialog()
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };
	HWND hwnd = nullptr;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
	ofn.lpstrFilter = TEXT("All Files\0*.*\0Text Files\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return FString(ofn.lpstrFile);
	}
	return FString();
}

void ADroneGameMode::LoadLidarPointCloud(const FString& FilePath)
{
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lidar file not found: %s"), *FilePath);
		return;
	}

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
		UE_LOG(LogTemp, Error, TEXT("Failed to load Lidar Point Cloud from file: %s"), *FilePath);
	}
}