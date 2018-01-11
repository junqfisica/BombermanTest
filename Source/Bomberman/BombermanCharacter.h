// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DamageInterface.h"
#include "BombermanCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerStatus : uint8
{
	Alive,
	Dead
};


UCLASS(Blueprintable)
class ABombermanCharacter : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	ABombermanCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;


	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

public:

	//~Beging Interfaces
	virtual void ReciveDamage(int32 DamageTake) override; // Ps: Adding =0 forces actor that implement this interface to defining it.
	//~End Interfaces

	// Status to check if player is dead or alive.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	EPlayerStatus PlayerStatus;

	/** This function adds boms to player
	*@param Value -> the number of bombs to add if possible
	*/
	UFUNCTION(BlueprintCallable, Category = "Bombs")
	void AddBomb(int32 Value);

	/** This function returns the number of avaible bombs*/
	UFUNCTION(BlueprintPure, Category = "Bombs")
	int32 GetCurrentAvaibleBombs();
	 
	/** This function try to spawn a bomb when player press key*/
	UFUNCTION(BlueprintCallable, Category = "Bombs")
	void TryToSpwanBomb();

private:

	// Curent number of bombs that player can use.
	int32 CurrentAvaibleBombs;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The Character base speed in unit/sec
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "10.0"))
	float BaseSpeed;

	// Modify the BaseSpeed by a factor x. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SpeedFactor;

	// The maximum number of bombs the player can drop.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bombs", meta = (ClampMin = "1"))
	int32 MaxAvaibleOfBombs;

};


