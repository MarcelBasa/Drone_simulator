#include "LIDARMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "LidarPointCloudComponent.h"
#include "LidarPointCloud.h"
#include <windows.h>
#include <commdlg.h>
#include "LidarPointCloudActor.h" 
#include "Drone_simulator/Controllers/DroneController.h"
#include "Drone_simulator/GameInstance/DroneGameInstance.h"


void ULIDARMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ChooseFileButton->OnClicked.AddDynamic(this, &ThisClass::ChooseFile);
	RunMapButton->OnClicked.AddDynamic(this, &ThisClass::RunMap);
	BackButton->OnClicked.AddDynamic(this, &ThisClass::Back);

	DroneController = Cast<ADroneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeUIOnly());
		DroneController->bShowMouseCursor = true;
	}
}

void ULIDARMenu::ChooseFile()
{
	SelectedFilePath = OpenFileDialog();
	if (!SelectedFilePath.IsEmpty())
	{
		if (!FPaths::FileExists(SelectedFilePath))
		{
			ChosenFileText->SetText(FText::FromString(FString("Lidar file not found")));
			ChosenFileText->SetColorAndOpacity(FLinearColor::Red);
			return;
		}

		if (SelectedFilePath.EndsWith(TEXT(".las")) || SelectedFilePath.EndsWith(TEXT(".laz")))
		{
			DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (DroneGameInstance)
			{
				DroneGameInstance->SetFilePath(SelectedFilePath);

				ChosenFileText->SetText(FText::FromString(SelectedFilePath));
				ChosenFileText->SetColorAndOpacity(FLinearColor::Green);
			}
		}
		else
		{
			ChosenFileText->SetText(FText::FromString(FString("Wrong file format")));
			ChosenFileText->SetColorAndOpacity(FLinearColor::Red);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No file selected"));
	}
}

void ULIDARMenu::RunMap()
{
	DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!DroneGameInstance || DroneGameInstance->GetFilePath().IsEmpty())
	{
		return;
	}
	
	if (DroneController)
	{
		DroneController->SetInputMode(FInputModeGameOnly());
		DroneController->bShowMouseCursor = false;
	}

	FName mapPath = FName("D:/UE_5_projekty_D/Drone_simulator/Content/Maps/Szczecin_LIDAR");
	UGameplayStatics::OpenLevel(GetWorld(), mapPath);
}

void ULIDARMenu::Back()
{
	if (DroneController)
		DroneController->HandleSetMenu();
}

FString ULIDARMenu::OpenFileDialog()
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