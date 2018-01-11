// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DamageInterface.h"
#include "Bomb.generated.h"


UCLASS()
class BOMBERMAN_API ABomb : public AActor, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABomb();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TimeHandler for bomb explosion
	FTimerHandle ExplodeTimeHandler;

	// Call OnExplode
	void Explode();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handle Bomb explosion.
	UFUNCTION(BlueprintNativeEvent, Category = "Bomb")
	void OnExplode(const TArray<FHitResult>& HitResults);
	virtual void OnExplode_Implementation(const TArray<FHitResult>& HitResults);

	//~Beging Interfaces
	virtual void ReciveDamage(int32 DamageTake) override; // Ps: Adding =0 forces actor that implement this interface to defining it.
	//~End Interfaces


private:

	// Static mesh for visual
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	/**
	Check for overlaps and collisions at the given direction
	@param Start -> Start Location trace.
	@param End-> Possible end Location for the trace.
	*/
	void ExplodeToDirection(const FVector& Start, const FVector&End);

	// Parameter to store the final locations for the explosion.
	class TArray<FVector> ExplosionEndLocations;

	// Array that chaches the hit results for colision. This is passed as argument to OnExplode.
	// Can be useful for Cosmetics.
	TArray<FHitResult> HitResults;

	// true when bomb explode. 
	bool bBombTriggered = false;

	// Count down to destroy bomb.
	float CounterToDestroy;

protected:

	// Describe what this missile hit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
	FName ExplosionCollisionProfile;

	// Time that the Bomb takes to go off secs.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb", meta = (ClampMin = "0.0"))
	float TimeToExplode;

	// Time that the Bomb can still apply damage in secs.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb", meta = (ClampMin = "0.0"))
	float BlastDurantion;

	// Size of explosion in unreal units.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb", meta = (ClampMin = "0.0"))
	float ExplosionRange;


};

