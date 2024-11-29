#include "CameraMenu.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Drone_simulator/GameInstance/DroneGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpinBox.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Drone_simulator/GameModes/DroneGameMode.h"

void UCameraMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChooseFlyHeightSpinBox)
        ChooseFlyHeightSpinBox->OnValueChanged.AddDynamic(this, &ThisClass::OnFlyHeightChanged);

    if (ChooseFlySpeedSpinBox)
        ChooseFlySpeedSpinBox->OnValueChanged.AddDynamic(this, &ThisClass::OnFlySpeedChanged);

    if (StartGameButton)
        StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGameButtonClick);

	DroneGameInstance = Cast<UDroneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UCameraMenu::OnFlyHeightChanged(float NewValue)
{
	if (DroneGameInstance)
		DroneGameInstance->SetDroneFlyHeight(NewValue);
}

void UCameraMenu::OnFlySpeedChanged(float NewValue)
{
    if (DroneGameInstance)
        DroneGameInstance->SetDroneFlySpeed(NewValue);
}

FReply UCameraMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();

    if (MapArea && MapArea->IsVisible())
    {
        FGeometry MapGeometry = MapArea->GetCachedGeometry();

        if (MapGeometry.IsUnderLocation(MousePosition))
        {
            FVector2D LocalMousePosition = MapGeometry.AbsoluteToLocal(MousePosition);
            FVector2D MapSize = MapGeometry.GetLocalSize();

            FVector2D NormalizedPosition(
                LocalMousePosition.X / MapSize.X,
                LocalMousePosition.Y / MapSize.Y
            );

            FVector2D RealMapSize(53000.0f, 53000.0f); 
            FVector2D RealWorldPosition(
                NormalizedPosition.X * RealMapSize.X,  
                NormalizedPosition.Y * RealMapSize.Y  
            );

            if (DroneGameInstance)
                DroneGameInstance->AddPointFly(RealWorldPosition);

            UUserWidget* DotWidget = CreateWidget<UUserWidget>(GetWorld(), DotWidgetClass);
            if (DotWidget)
            {
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Background->AddChild(DotWidget));
                if (CanvasSlot)
                {
                    CanvasSlot->SetPosition(LocalMousePosition);
                    CanvasSlot->SetSize(FVector2D(DotSize));
                }
            }
            return FReply::Handled();
        }
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCameraMenu::OnStartGameButtonClick()
{
    if (DroneGameInstance && DroneGameInstance->GetFlyPoints().Num() >= 2)
    {
        ADroneGameMode* DroneGameMode = Cast<ADroneGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
        if (DroneGameMode)
            DroneGameMode->StartGame(DroneGameInstance->GetFlyPoints()[0]);
        if (DroneController)
        {
            DroneController->SetInputMode(FInputModeGameOnly());
            DroneController->bShowMouseCursor = false;
        }
        RemoveFromParent();
    }
}