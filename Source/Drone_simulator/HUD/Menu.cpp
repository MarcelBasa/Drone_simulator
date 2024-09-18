#include "Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &ThisClass::Quit);
	LidarButton->OnClicked.AddDynamic(this, &ThisClass::ChooseLidar);
	OrtofotomapaButton->OnClicked.AddDynamic(this, &ThisClass::ChooseOrtofotomapa);

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
		PlayerController->bShowMouseCursor = true;
}

void UMenu::Quit()
{
	if (PlayerController)
		PlayerController->ConsoleCommand("quit");
}

void UMenu::ChooseLidar()
{
	LoadMap("Szczecin_LIDAR.umap");
}

void UMenu::ChooseOrtofotomapa()
{
	LoadMap("Szczecin_Ortofotomapa.umap");
}

void UMenu::LoadMap(FString mapName)
{
	if (PlayerController)
		PlayerController->bShowMouseCursor = false;

	FString mapPath = "D:/UE_5_projekty_D/Drone_simulator/Content/Maps/" + mapName;
	UGameplayStatics::OpenLevel(GetWorld(), FName(mapPath));
}