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
	ExplosionRange = 500.0f;
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

	GetWorldTimerManager().SetTimer(ExplodeTimeHandler, this, &ABomb::Explode,TimeToExplode);

	
}

void ABomb::Explode()
{

	// 
	FVector Loc = GetActorLocation();
	FVector DesiredEndLocUP = Loc + ExplosionRange*GetActorForwardVector();
	FVector DesiredEndLocDown = Loc - ExplosionRange*GetActorForwardVector();
	FVector DesiredEndLocRight = Loc + ExplosionRange*GetActorRightVector();
	FVector DesiredEndLocLeft = Loc - ExplosionRange*GetActorRightVector();

	ExplodeToDirection(Loc, DesiredEndLocUP);
	ExplodeToDirection(Loc, DesiredEndLocDown);
	ExplodeToDirection(Loc, DesiredEndLocRight);
	ExplodeToDirection(Loc, DesiredEndLocLeft);

	OnExplode(HitResults);
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::OnExplode_Implementation(const TArray<FHitResult>& HitResults)
{
	UE_LOG(LogTemp, Warning, TEXT("Explode"));
}

void ABomb::ExplodeToDirection(const FVector & Start, const FVector & End)
{
	UWorld* World = GetWorld();
	TArray<FHitResult> OutResults;

	if(World != nullptr)
	{
		FVector HitLocation = End;

		if(World->LineTraceMultiByProfile(OutResults, Start, End, ExplosionCollisionProfile))
		{//Collide.
			// Only true when hit
			HitResults.Add(OutResults.Last());
			UE_LOG(LogTemp, Warning, TEXT("Colllide"));
			HitLocation = OutResults.Last().Location;

		}
		else
		{// Possibles overlaps.
			// May have some Overlap
			for (FHitResult Overlap : OutResults)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap"));
				UKismetSystemLibrary::DrawDebugCircle(World, Overlap.Location, 50.0f,12,FColor::Green,5.0f,5.0f); // Debug
			}
		}
		UKismetSystemLibrary::DrawDebugLine(World, Start, HitLocation, FColor::Red, 5.0f, 10.0f); // Debug
	}
	
}

