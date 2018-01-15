// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUps.generated.h"


UENUM(BlueprintType)
enum class EPickups : uint8
{
	MoreBomb,
	LongerBlast,
	RunFaster,
	Remotebomb
};

UCLASS()
class BOMBERMAN_API APickUps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Type of this pick up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ExposeOnSpawn = true))
	EPickups PickupType;


private:

	// Static mesh for visual
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;
	
};
