// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString textToDisplay)
{
	if (DisplayText) {
		DisplayText->SetText(FText::FromString(textToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* inPawn)
{
	ENetRole localRole = inPawn->GetLocalRole();
	FString role;

	switch (localRole)
	{
	case ROLE_None:
		role = FString("None");
		break;
	case ROLE_SimulatedProxy:
		role = FString("Simulated Proxy");
		break;
	case ROLE_AutonomousProxy:
		role = FString("Autonomous Proxy");
		break;
	case ROLE_Authority:
		role = FString("Authority");
		break;
	case ROLE_MAX:
		role = FString("MAX");
		break;
	default:
		break;
	}

	FString loadlRoleString = FString::Printf(TEXT("Local Role: %s"), *role);
	SetDisplayText(loadlRoleString);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
	
}

 
FString UOverheadWidget::GetRemoteRole(APawn* inPawn)
{
    ENetRole remoteRole = inPawn->GetRemoteRole();
    FString role;

    switch (remoteRole)
    {
    case ROLE_None:
        role = FString("None");
        break;
    case ROLE_SimulatedProxy:
        role = FString("Simulated Proxy");
        break;
    case ROLE_AutonomousProxy:
        role = FString("Autonomous Proxy");
        break;
    case ROLE_Authority:
        role = FString("Authority");
        break;
    case ROLE_MAX:
        role = FString("MAX");
        break;
    default:
        break;
    }

    FString remoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *role);
    return remoteRoleString;
}




