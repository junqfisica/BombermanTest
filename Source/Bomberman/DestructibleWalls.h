// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DamageInterface.h"
#include "DestructibleWalls.generated.h"

UCLASS()
class BOMBERMAN_API ADestructibleWalls : public AActor, public IDamageInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//~Beging Interfaces
	virtual void ReciveDamage(int32 DamageTake) override; // Ps: Adding =0 forces actor that implement this interface to defining it.
	//~End Interfaces

private:

	// Static mesh for visual
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

protected:

	//Event to Spawn pickup.Parent should be call at the end of this Event.
	UFUNCTION(BlueprintNativeEvent, Category = "Pickups")
	void SpawnPickup();
	virtual void SpawnPickup_Implementation();

	// Probability of droping a pickup. (From 1 to 100)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickups", meta =  (ClampMin = "1" , ClampMax = "100"))
	int32 ChangeOfDropPowerUps;

	
};
