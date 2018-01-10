// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "BombermanCharacter.h"

void FBomerInput::Sanitize()
{
	MovimentInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovimentInput.Normalize();
	RawMovementInput.Set(0.0f, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Moviment: %f, %f"),MovimentInput.X,MovimentInput.Y);
}

void FBomerInput::MoveX(float AxisValue)
{
	RawMovementInput.X = AxisValue;
}

void FBomerInput::MoveY(float AxisValue)
{
	RawMovementInput.Y = AxisValue;
}

void FBomerInput::Fire(bool bPressed)
{
	bFire = bPressed;
}


ABombermanPlayerController::ABombermanPlayerController()
{
	bShowMouseCursor = false;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;

}

void ABombermanPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	Player1Input.Sanitize();
	Player2Input.Sanitize();
	
	{// Move Player 1
		FVector DesiredMovimentDirection = FVector(Player1Input.MovimentInput.X, Player1Input.MovimentInput.Y, 0.0f);
		if (!DesiredMovimentDirection.IsNearlyZero())
		{
			if (ACharacter* const MyChar = GetCharacter())
			{

				MyChar->AddMovementInput(DesiredMovimentDirection, 1.0f);

			}
		}
	}

	{// Move player 2
		FVector DesiredMovimentDirection = FVector(Player2Input.MovimentInput.X, Player2Input.MovimentInput.Y, 0.0f);
		if (!DesiredMovimentDirection.IsNearlyZero())
		{
			if (Player2 != nullptr)
			{
				Player2->AddMovementInput(DesiredMovimentDirection, 1.0f);
			}

		}
	}
}

void ABombermanPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ABombermanPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ABombermanPlayerController::OnSetDestinationReleased);
	InputComponent->BindAxis("MoveForward",this, &ABombermanPlayerController::MoveFoward);
	InputComponent->BindAxis("MoveRight", this, &ABombermanPlayerController::MoveRight);

	InputComponent->BindAxis("MoveForward2", this, &ABombermanPlayerController::MoveFoward2);
	InputComponent->BindAxis("MoveRight2", this, &ABombermanPlayerController::MoveRight2);

	// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABombermanPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABombermanPlayerController::MoveToTouchLocation);

}


void ABombermanPlayerController::MoveFoward(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moviment: %f"),AxisValue);
	Player1Input.MoveX(AxisValue);
}

void ABombermanPlayerController::MoveRight(float AxisValue)
{
	Player1Input.MoveY(AxisValue);
}

void ABombermanPlayerController::MoveFoward2(float AxisValue)
{
	Player2Input.MoveX(AxisValue);
}

void ABombermanPlayerController::MoveRight2(float AxisValue)
{
	Player2Input.MoveY(AxisValue);
}
