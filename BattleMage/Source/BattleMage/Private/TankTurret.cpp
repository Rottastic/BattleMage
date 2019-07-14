// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

#include "CoreMinimal.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Given the maximum aiming speed and dTime, rotate tank to aim, iterate
	// Rotate the turret horizontally towards the target
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	// Temporary fix for the turret/barrel jitters
	if (RotationChange < 4.f && RotationChange > 1.f)
	{
		RotationChange = 1.f;
	}
	else if (RotationChange > -4.f && RotationChange < -1.f)
	{
		RotationChange = -1.f;
	}
	else if (RotationChange >= -1.f && RotationChange <= 1.f)
	{
		RotationChange = 0.f;
	}
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	float NewRotation = RawNewRotation;

	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}




