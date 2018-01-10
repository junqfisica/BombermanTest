// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"

ABombermanCharacter::ABombermanCharacter()
{

	BaseSpeed = 400.0f;
	SpeedFactor = 1.0f;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(50.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed*SpeedFactor;


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ABombermanCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed*SpeedFactor;
}


void ABombermanCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// Change MAxWalkSpeed if SpeedFactorChange
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed*SpeedFactor;
	

}