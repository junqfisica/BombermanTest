// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS(Blueprintable)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABombermanCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	
	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The Character base speed in unit/sec
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "10.0"))
	float BaseSpeed;

	// Modify the BaseSpeed by a factor x. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SpeedFactor;

};

