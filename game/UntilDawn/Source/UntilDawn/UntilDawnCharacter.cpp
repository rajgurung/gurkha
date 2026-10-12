// Copyright Epic Games, Inc. All Rights Reserved.

#include "UntilDawnCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UntilDawn.h"

AUntilDawnCharacter::AUntilDawnCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// the first person camera rides on this mesh's head bone, so keep its bones updated while the owner cannot see it
	FirstPersonMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// Create the third person camera boom. The camera manager blends from its end point to the first person camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;

	// configure the character comps.
	// The body is visible to the owner in third person, so it cannot be a first person world space representation,
	// which forces owner-no-see. Keep its shadow while it is hidden for aiming.
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::None;
	GetMesh()->bCastHiddenShadow = true;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AUntilDawnCharacter::BeginPlay()
{
	Super::BeginPlay();

	// apply here as well as in the constructor, in case a Blueprint overrides the body's first person type
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::None);

	// start in third person
	bFirstPersonView = true;
	SetFirstPersonView(false);
}

void AUntilDawnCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// read the camera tuning every frame so edits apply during Play
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, CameraPivotHeight));
	CameraBoom->TargetArmLength = CameraArmLength;
	CameraBoom->SocketOffset = FVector(0.0f, CameraShoulderOffset, 0.0f);
	CameraBoom->ProbeSize = CameraProbeRadius;
}

void AUntilDawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AUntilDawnCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUntilDawnCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUntilDawnCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUntilDawnCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AUntilDawnCharacter::MouseLookInput);

		// Aiming down the sights (hold)
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AUntilDawnCharacter::DoStartAiming);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AUntilDawnCharacter::DoStopAiming);
	}
	else
	{
		UE_LOG(LogUntilDawn, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AUntilDawnCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AUntilDawnCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis, scaled by the gamepad sensitivity
	FVector2D LookAxisVector = Value.Get<FVector2D>() * GamepadLookScale * (bAimHeld ? AimLookMultiplier : 1.0f);

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AUntilDawnCharacter::MouseLookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis, scaled by the mouse sensitivity
	FVector2D LookAxisVector = Value.Get<FVector2D>() * MouseLookScale * (bAimHeld ? AimLookMultiplier : 1.0f);

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AUntilDawnCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AUntilDawnCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AUntilDawnCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AUntilDawnCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AUntilDawnCharacter::DoStartAiming()
{
	bAimHeld = true;
}

void AUntilDawnCharacter::DoStopAiming()
{
	bAimHeld = false;
}

void AUntilDawnCharacter::SetFirstPersonView(bool bFirstPerson)
{
	if (bFirstPerson == bFirstPersonView)
	{
		return;
	}

	bFirstPersonView = bFirstPerson;

	// the arms mesh is only ever seen by the owner, so hiding it from the owner hides it completely
	GetFirstPersonMesh()->SetOwnerNoSee(!bFirstPerson);
	GetMesh()->SetOwnerNoSee(bFirstPerson);
}
