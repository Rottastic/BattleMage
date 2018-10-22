// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Given the maximum aiming speed and dTime, rotate tank to aim, iterate
	// Rotate the turret horizontally towards the target
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + ElevationChange;
	float NewRotation = RawNewRotation;
	//float NewRotation = FMath::Clamp(RawNewRotation, -MaxRotationDegrees, MaxRotationDegrees);
	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}




