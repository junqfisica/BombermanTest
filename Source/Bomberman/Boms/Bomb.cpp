// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
ABomb::ABomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeToExplode = 2.0f;
	BlastDurantion = 5.0f;
	ExplosionRange = 500.0f;
	ExplosionCollisionProfile = "Bomb:Explosion"; // Not so safe, but it's ok for now.

	CounterToDestroy = BlastDurantion;

	{// Set Components

		if (!RootComponent)
		{// Attach a scene component if there is none.
			RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BombRoot"));
		}

		StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombBody"));
		StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ExplodeTimeHandler, this, &ABomb::Explode, TimeToExplode);

	{// Store the end locations for explosion
		FVector Loc = GetActorLocation();
		ExplosionEndLocations.Add(Loc + ExplosionRange*GetActorForwardVector());
		ExplosionEndLocations.Add(Loc - ExplosionRange*GetActorForwardVector());
		ExplosionEndLocations.Add(Loc + ExplosionRange*GetActorRightVector());
		ExplosionEndLocations.Add(Loc - ExplosionRange*GetActorRightVector());

	}



}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBombTriggered == true)
	{
		FVector Loc = GetActorLocation();

		for (FVector EndLocation : ExplosionEndLocations)
		{
			ExplodeToDirection(Loc, EndLocation);
		}

		CounterToDestroy -= DeltaTime;
		if (CounterToDestroy <= 0.0f)
		{// Destroy this actor.
			bBombTriggered = false;
			Destroy();
		}
	}
}

void ABomb::Explode()
{

	//Turn Collision off when explode.
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// Clear TimeHandler of explosion.
	GetWorldTimerManager().ClearTimer(ExplodeTimeHandler);

	FVector Loc = GetActorLocation();

	// Explode to four directions.
	for (FVector EndLocation : ExplosionEndLocations)
	{
		ExplodeToDirection(Loc, EndLocation);
	}

	OnExplode(HitResults);

	bBombTriggered = true;

}

void ABomb::OnExplode_Implementation(const TArray<FHitResult>& HitResults)
{
	UE_LOG(LogTemp, Warning, TEXT("Explode"));
}

void ABomb::ReciveDamage(int32 DamageTake)
{
	Explode();
}

void ABomb::ExplodeToDirection(const FVector & Start, const FVector & End)
{
	UWorld* World = GetWorld();
	TArray<FHitResult> OutResults;

	if (World != nullptr)
	{
		FVector HitLocation = End;

		if (World->LineTraceMultiByProfile(OutResults, Start, End, ExplosionCollisionProfile))
		{//Collide. Only true when hit

			if (!bBombTriggered)
			{// Do it only once. To check for hits. 

				HitResults.Add(OutResults.Last());

				//For Debug
				UE_LOG(LogTemp, Warning, TEXT("Colllide"));
				HitLocation = OutResults.Last().Location;
			}

		}
		else
		{// Possibles overlaps.
		 // May have some Overlap
			for (FHitResult Overlap : OutResults)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap"));
				UKismetSystemLibrary::DrawDebugCircle(World, Overlap.Location, 50.0f, 12, FColor::Green, BlastDurantion, 5.0f); // Debug overlap
				if (IDamageInterface* DamageActor = Cast<IDamageInterface>(Overlap.GetActor()))
				{
					DamageActor->ReciveDamage(0);
				}
			}
		}

		if (!bBombTriggered)
		{
			UKismetSystemLibrary::DrawDebugLine(World, Start, HitLocation, FColor::Red, BlastDurantion, 10.0f); // Debug Collision
		}

	}
}


