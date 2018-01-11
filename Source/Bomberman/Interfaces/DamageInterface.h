// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
*
*/
class BOMBERMAN_API IDamageInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ReciveDamage(int32 DamageTake) = 0; // Ps: Adding =0 forces actor that implement this interface to define it.

};

