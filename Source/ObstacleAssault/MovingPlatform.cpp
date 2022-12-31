// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	currentLocation = currentLocation + (PlatformVelocity * DeltaTime);
	SetActorLocation(currentLocation);

	double distMoved = FVector::Dist(currentLocation, StartLocation);

	if (distMoved >= MoveDistance) {
		float offset = (distMoved - MoveDistance);
		UE_LOG(LogTemp, Display, TEXT("Overshoot: %s %f"), *GetName(), offset);

		FVector moveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (moveDirection * MoveDistance);

		PlatformVelocity = PlatformVelocity * -1;
	}
}
