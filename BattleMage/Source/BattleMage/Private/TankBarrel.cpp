// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Given the maximum aiming speed and dTime, rotate tank to aim, iterate
	// Rotate the barrel to aim at target
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float NewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevation, 0.f, 0.f));


}

