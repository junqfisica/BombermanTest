// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUps.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APickUps::APickUps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	{// Set Components

		if (!RootComponent)
		{// Attach a scene component if there is none.
			RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
		}

		StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpBody"));
		StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		StaticMesh->SetCollisionProfileName("Pickups:General");
		StaticMesh->Mobility = EComponentMobility::Stationary;
		StaticMesh->CastShadow = false;
	}
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

