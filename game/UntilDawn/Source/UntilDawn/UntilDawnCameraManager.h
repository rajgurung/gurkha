// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "UntilDawnCameraManager.generated.h"

/**
 *  Camera manager for the third person / first person aim camera (decision 0002).
 *  Blends one view between the character's camera boom and its first person camera by an aim alpha.
 *  Limits min/max look pitch.
 */
UCLASS(config=Game)
class AUntilDawnCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:

	/** Field of view in third person */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "deg"))
	float ThirdPersonFOV = 72.0f;

	/** Field of view while aiming */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "deg"))
	float AimFOV = 65.0f;

	/** Time to blend into the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (ClampMin = 0, Units = "s"))
	float AimInTime = 0.20f;

	/** Time to blend out of the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (ClampMin = 0, Units = "s"))
	float AimOutTime = 0.15f;

	/** Aim alpha at which the body is swapped for the first person arms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (ClampMin = 0, ClampMax = 1))
	float AimViewSwapAlpha = 0.5f;

	/** 0 in third person, 1 fully in the sights */
	float AimAlpha = 0.0f;

public:

	/** Constructor */
	AUntilDawnCameraManager();

	/** Returns 0 in third person, 1 fully in the sights */
	float GetAimAlpha() const { return AimAlpha; }

protected:

	/** Blends the view target's POV between the boom and the sights */
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
