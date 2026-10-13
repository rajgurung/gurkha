// Copyright Epic Games, Inc. All Rights Reserved.


#include "UntilDawnCameraManager.h"
#include "UntilDawnCharacter.h"
#include "GameFramework/SpringArmComponent.h"

AUntilDawnCameraManager::AUntilDawnCameraManager()
{
	// set the min/max pitch
	ViewPitchMin = -70.0f;
	ViewPitchMax = 80.0f;
}

void AUntilDawnCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	// let the base class fill the POV from the character's first person camera
	Super::UpdateViewTarget(OutVT, DeltaTime);

	AUntilDawnCharacter* Character = Cast<AUntilDawnCharacter>(OutVT.Target);
	if (!Character)
	{
		return;
	}

	// move the aim alpha towards the held state at the in or out rate
	if (Character->IsAiming())
	{
		AimAlpha = AimInTime > 0.0f ? FMath::Min(AimAlpha + DeltaTime / AimInTime, 1.0f) : 1.0f;
	}
	else
	{
		AimAlpha = AimOutTime > 0.0f ? FMath::Max(AimAlpha - DeltaTime / AimOutTime, 0.0f) : 0.0f;
	}

	// swap the body for the arms part way through the blend, so the body never fills the screen
	Character->SetFirstPersonView(AimAlpha >= AimViewSwapAlpha && AimAlpha > 0.0f);

	// blend from the boom end point to the sights. Both views use the control rotation
	const float Blend = FMath::SmoothStep(0.0f, 1.0f, AimAlpha);
	const FVector BoomLocation = Character->GetCameraBoom()->GetSocketLocation(USpringArmComponent::SocketName);

	OutVT.POV.Location = FMath::Lerp(BoomLocation, OutVT.POV.Location, Blend);
	OutVT.POV.FOV = FMath::Lerp(ThirdPersonFOV, AimFOV, Blend);
}
