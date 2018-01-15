// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleWalls.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ADestructibleWalls::ADestructibleWalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChangeOfDropPowerUps = 30;

	{// Set Components

		if (!RootComponent)
		{// Attach a scene component if there is none.
			RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DestructibleRoot"));
		}

		StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestructibleBody"));
		StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

}

// Called when the game starts or when spawned
void ADestructibleWalls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADestructibleWalls::ReciveDamage(int32 DamageTake)
{
	bool bShouldDrop = FMath::RandRange(1, 100 / ChangeOfDropPowerUps) == 1 ? true : false; // This has ChangeOfDropPowerUps% change to happen
	if(bShouldDrop)
	{
		UE_LOG(LogTemp, Warning, TEXT("DropIten"));
		SpawnPickup();
	}
	else
	{
		Destroy(); // Only destroy direct if not drop an iten. Otherwise, the destroy will be done at SpawnPickup_Implementation
	}

}

void ADestructibleWalls::SpawnPickup_Implementation()
{
	// Destroy this actor. Ps: Run this node in Blueprint for the last.
	Destroy();	
}


