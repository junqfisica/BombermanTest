// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"

ABombermanCharacter::ABombermanCharacter()
{

	BaseSpeed = 400.0f;
	SpeedFactor = 1.0f;
	PlayerStatus = EPlayerStatus::Alive;
	MaxAvaibleOfBombs = 1;
	BombBlastFactor = 1.0f;
	CurrentAvaibleBombs = MaxAvaibleOfBombs;

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

void ABombermanCharacter::ReciveDamage(int32 DamageTake)
{
	//
	UE_LOG(LogTemp, Warning, TEXT("Player die"));

	//Turn Collision off Overlap once.
	GetCapsuleComponent()->SetCollisionProfileName("IgnoreBomb:Only");

	PlayerStatus = EPlayerStatus::Dead;

}

void ABombermanCharacter::AddBomb(int32 Value)
{
	CurrentAvaibleBombs = FMath::Clamp(CurrentAvaibleBombs + Value, 0, MaxAvaibleOfBombs);
	 
}

int32 ABombermanCharacter::GetCurrentAvaibleBombs()
{
	return CurrentAvaibleBombs;
}

void ABombermanCharacter::TryToSpwanBomb()
{
	if(CurrentAvaibleBombs > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DropBomb"));
		CurrentAvaibleBombs = FMath::Clamp(CurrentAvaibleBombs - 1, 0, MaxAvaibleOfBombs);
		SpawnBomb();
	}
}


// Active Power Ups.
void ABombermanCharacter::ActivatePowerUp(EPickups Pickuptype)
{
	switch (Pickuptype)
	{
	case EPickups::LongerBlast:
	{
		UE_LOG(LogTemp, Warning, TEXT("LongerBlast Activation"));
		// Increase blast size in 20% each time player gets this pickup. Max allow 2x.
		BombBlastFactor = FMath::Clamp(BombBlastFactor + 0.2f, 1.0f, 2.0f);
		break;
	}

	case EPickups::MoreBomb:
	{
		UE_LOG(LogTemp, Warning, TEXT("MoreBomb Activation"));
		// Add more avaible bombs to player
		MaxAvaibleOfBombs++;
		AddBomb(1);
		break;
	}

	case EPickups::Remotebomb:
		UE_LOG(LogTemp, Warning, TEXT("Remotebomb Activation"));
		break;

	case EPickups::RunFaster:
	{
		UE_LOG(LogTemp, Warning, TEXT("RunFaster Activation"));
		// Increase speed in 20% each time player gets this pickup. Max allow 2x.
		SpeedFactor = FMath::Clamp(SpeedFactor + 0.2f, 0.0f, 2.0f);
		break;
	}
		

	default:
		break;
	}
}

void ABombermanCharacter::SpawnBomb_Implementation()
{
	//Add funtionality when spawn bomb, if necessary
}
