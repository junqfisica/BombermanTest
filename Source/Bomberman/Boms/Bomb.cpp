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
	BlastDurantion = 1.2f;
	ExplosionSize = 150.0f;
	ExplosionCollisionProfile = "Bomb:Explosion"; // Not so safe, but it's ok for now.

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

	// Store the end locations for explosion
	SetExplosionEndLocations(ExplosionSize);

	// Sets counter equal the durantion of blast.
	CounterToDestroy = BlastDurantion;

}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBombTriggered == true)
	{// When bomb is triggered check for overlaps until it's destroyed.

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

	// Clear ExplodeTimeHandler.
	if(ExplodeTimeHandler.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ExplodeTimeHandler);
	}
	

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

void ABomb::IncreaseBombBlast(float Percent)
{
	ExplosionSize = ExplosionSize*Percent;
	// Store the end locations for explosion
	SetExplosionEndLocations(ExplosionSize);
}

void ABomb::TurnOffAutoExplosion()
{
	if (ExplodeTimeHandler.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ExplodeTimeHandler);
	}
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

			// May have some Overlap
			int32 RemoveLastIndex = OutResults.Num() - 1;
			OutResults.RemoveAt(RemoveLastIndex); // Remove the collision hit. Note necessary.
			CheckForOverlaps(OutResults);
		}
		else
		{// May have some Overlap

			CheckForOverlaps(OutResults);
		}

		if (!bBombTriggered)
		{
			UKismetSystemLibrary::DrawDebugLine(World, Start, HitLocation, FColor::Red, BlastDurantion, 10.0f); // Debug Blast
		}

	}
}

void ABomb::CheckForOverlaps(const TArray<FHitResult> & OverlapsResult)
{
	UWorld* World = GetWorld();
	if(World != nullptr)
	{
		for (FHitResult Overlap : OverlapsResult)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlap"));
			UKismetSystemLibrary::DrawDebugCircle(World, Overlap.Location, 50.0f, 12, FColor::Green, BlastDurantion, 5.0f); // Debug overlap
			if (IDamageInterface* DamageActor = Cast<IDamageInterface>(Overlap.GetActor()))
			{
				DamageActor->ReciveDamage(0);
			}
		}
	}

}

void ABomb::SetExplosionEndLocations(float Range)
{
	{// Store the end locations for explosion
		FVector Loc = GetActorLocation();
		if(ExplosionEndLocations.Num() == 0)
		{
			ExplosionEndLocations.Add(Loc + Range*GetActorForwardVector());
			ExplosionEndLocations.Add(Loc - Range*GetActorForwardVector());
			ExplosionEndLocations.Add(Loc + Range*GetActorRightVector());
			ExplosionEndLocations.Add(Loc - Range*GetActorRightVector());
		}
		else
		{
			// Clear Array first.
			ExplosionEndLocations.Empty();

			ExplosionEndLocations.Add(Loc + Range*GetActorForwardVector());
			ExplosionEndLocations.Add(Loc - Range*GetActorForwardVector());
			ExplosionEndLocations.Add(Loc + Range*GetActorRightVector());
			ExplosionEndLocations.Add(Loc - Range*GetActorRightVector());	
		}
		

	}
}


