// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BombermanPlayerController.generated.h"


//Struc for handle player input
USTRUCT(BlueprintType)
struct FBomerInput
{
	GENERATED_BODY()

	// Useful to debug orientation.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerInput")
	FVector2D MovimentInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerInput")
	bool bFire;

	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void Fire(bool bPressed);

private:

	FVector2D RawMovementInput;
};

UCLASS()
class ABombermanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABombermanPlayerController();



protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for MovePlayer1*/
	void MoveFoward(float AxisValue);
	void MoveRight(float AxisValue);

	/** Input handlers for MovePlayer2*/
	void MoveFoward2(float AxisValue);
	void MoveRight2(float AxisValue);


	
	// Structure that recives player's input
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerInput")
	FBomerInput Player1Input;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerInput")
	FBomerInput Player2Input;

	// Variable to store player 2. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInput")
	class ABombermanCharacter* Player2;
	

};


