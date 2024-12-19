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
#include "Drone_simulator/HUD/FlyPoint.h"
#include "Drone_simulator/HUD/FlyHeight.h"

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
    if (DroneGameInstance &&
        ChooseFlyHeightSpinBox&&
        ChooseFlySpeedSpinBox
        )
    {
        ChooseFlyHeightSpinBox->SetValue(DroneGameInstance->GetDroneFlyHeight());
        ChooseFlySpeedSpinBox->SetValue(DroneGameInstance->GetDroneFlySpeed());
    }
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
                DroneGameInstance->AddPointFly(RealWorldPosition.X, RealWorldPosition.Y);
       
            SetDotHeightEditor(LocalMousePosition);
            SetDotWidget(LocalMousePosition);
            dotCount++;

            return FReply::Handled();
        }
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCameraMenu::SetDotWidget(FVector2D mousePosition)
{
    if (!DotWidgetClass) return;

    UFlyPoint* DotWidget = CreateWidget<UFlyPoint>(GetWorld(), DotWidgetClass);
    if (DotWidget)
    {
        DotWidget->setNumber(dotCount);
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Background->AddChild(DotWidget));
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(mousePosition);
            CanvasSlot->SetSize(FVector2D(DotSize));
        }
    }
}

void UCameraMenu::SetDotHeightEditor(FVector2D mousePosition)
{
    if (!FlyHeightWidgetClass) return;

    UFlyHeight* FlyHeightWidget = CreateWidget<UFlyHeight>(GetWorld(), FlyHeightWidgetClass);
    if (FlyHeightWidget)
    {
        FVector* FlyPoint = DroneGameInstance->GetFlyPoint(dotCount);
        if(FlyPoint)
            FlyHeightWidget->SetFlyPointRef(*FlyPoint);
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Background->AddChild(FlyHeightWidget));
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(mousePosition);
            CanvasSlot->SetSize(FVector2D(250, 100));
        }
    }
}

void UCameraMenu::OnStartGameButtonClick()
{
    if (DroneGameInstance && DroneGameInstance->GetFlyPoints().Num() >= 2)
    {
        DroneGameInstance->Reset();
        dotCount = 0;
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