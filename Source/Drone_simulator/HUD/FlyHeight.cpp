#include "FlyHeight.h"
#include "Components/SpinBox.h"


void UFlyHeight::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChooseFlyHeightSpinBox)
		ChooseFlyHeightSpinBox->OnValueChanged.AddDynamic(this, &ThisClass::OnFlyHeightChanged);

}

void UFlyHeight::OnFlyHeightChanged(float NewValue)
{
	FlyPointRef->Z = NewValue;
	UE_LOG(LogTemp, Warning, TEXT("%f"), NewValue);
}

void UFlyHeight::SetFlyPointRef(FVector& FlyPoint)
{
	FlyPointRef = &FlyPoint;
	ChooseFlyHeightSpinBox->SetValue(FlyPointRef->Z);
}