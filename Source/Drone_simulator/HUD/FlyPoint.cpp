#include "FlyPoint.h"
#include "Components/TextBlock.h"


void UFlyPoint::setNumber(int32 count)
{
	if(TextNumber)
		TextNumber->SetText(FText::AsNumber(count));
}