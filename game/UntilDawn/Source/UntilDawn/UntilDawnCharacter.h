// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UntilDawnCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Third person character with a first person sight view while aiming (decision 0002).
 *  The camera manager blends between the boom view and the first person camera.
 */
UCLASS(abstract, config=Game)
class AUntilDawnCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Third person camera boom behind the right shoulder. Has no camera: the camera manager reads its end point */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	/** Aim (hold) Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* AimAction;

	/** Sprint (hold) Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* SprintAction;

	/** Multiplier applied to mouse look input. Default set in DefaultGame.ini */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Look")
	float MouseLookScale = 0.4f;

	/** Multiplier applied to gamepad look input. Default set in DefaultGame.ini */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Look")
	float GamepadLookScale = 1.0f;

	/** Look multiplier applied on top of the mouse and gamepad scales while aiming */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Look")
	float AimLookMultiplier = 0.6f;

	/** Third person camera arm length */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "cm"))
	float CameraArmLength = 200.0f;

	/** Sideways camera offset to the right shoulder */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "cm"))
	float CameraShoulderOffset = 45.0f;

	/** Height of the boom pivot above the capsule centre, at head height */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "cm"))
	float CameraPivotHeight = 70.0f;

	/** Radius of the camera collision probe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Camera", meta = (Units = "cm"))
	float CameraProbeRadius = 15.0f;

	/** Movement speed when not sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Movement", meta = (Units = "cm/s"))
	float WalkSpeed = 600.0f;

	/** Movement speed while sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category="Tuning|Movement", meta = (Units = "cm/s"))
	float SprintSpeed = 850.0f;

	/** True while the aim input is held */
	bool bAimHeld = false;

	/** True while the sprint input is held */
	bool bSprintHeld = false;

	/** True while the first person arms are shown instead of the body */
	bool bFirstPersonView = false;
	
public:
	AUntilDawnCharacter();

	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Called from Input Actions for mouse looking input */
	void MouseLookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handles aim start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoStartAiming();

	/** Handles aim end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoStopAiming();

	/** Handles sprint start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoStartSprinting();

	/** Handles sprint end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoStopSprinting();

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns the third person camera boom **/
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns true while the character should be in the sights: aim is held and no action drops it (rule 1) */
	virtual bool IsAiming() const { return bAimHeld && !bSprintHeld; }

	/** Shows the first person arms (true) or the full body (false) to the owner */
	virtual void SetFirstPersonView(bool bFirstPerson);

};

