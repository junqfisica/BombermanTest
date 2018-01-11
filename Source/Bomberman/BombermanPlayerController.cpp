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

	// Bind Inputs for Player 1
	InputComponent->BindAction("DropBomb", IE_Pressed, this, &ABombermanPlayerController::DropBombPressed);
	InputComponent->BindAction("DropBomb", IE_Released, this, &ABombermanPlayerController::DropBombRelease);
	InputComponent->BindAxis("MoveForward",this, &ABombermanPlayerController::MoveFoward);
	InputComponent->BindAxis("MoveRight", this, &ABombermanPlayerController::MoveRight);


	// Bind Inputs for Player 2
	InputComponent->BindAction("DropBomb2", IE_Pressed, this, &ABombermanPlayerController::DropBomb2Pressed);
	InputComponent->BindAction("DropBomb2", IE_Released, this, &ABombermanPlayerController::DropBomb2Release);
	InputComponent->BindAxis("MoveForward2", this, &ABombermanPlayerController::MoveFoward2);
	InputComponent->BindAxis("MoveRight2", this, &ABombermanPlayerController::MoveRight2);

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

void ABombermanPlayerController::DropBombPressed()
{
	Player1Input.Fire(true); // Useful in the case when we want to make spwan by pressing and hold.

	if (ABombermanCharacter* const Player1 = Cast<ABombermanCharacter>(GetCharacter()))
	{
		Player1->TryToSpwanBomb();
	}
}

void ABombermanPlayerController::DropBombRelease()
{
	Player1Input.Fire(false);
}

void ABombermanPlayerController::DropBomb2Pressed()
{
	Player2Input.Fire(true);

	if (Player2 != nullptr)
	{
		Player2->TryToSpwanBomb();
	}
}

void ABombermanPlayerController::DropBomb2Release()
{
	Player2Input.Fire(false);
}
