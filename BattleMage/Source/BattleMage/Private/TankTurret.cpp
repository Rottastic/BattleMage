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
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	float NewRotation = RawNewRotation;
	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}




