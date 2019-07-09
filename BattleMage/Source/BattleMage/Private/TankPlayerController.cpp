// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the tank's barrel to align a hit on the player
	AimAtCrosshair();
}


void ATankPlayerController::AimAtCrosshair()
{
	if (!ensure((AimingComponent && GetControlledTank()))) { return; }

	FVector HitLocation;
	if (GetCrosshairHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		return;
	}
}
bool ATankPlayerController::GetCrosshairHitLocation(FVector& OUT HitLocation) const
{
	// Find Crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrosshairXLocation), (ViewportSizeY * CrosshairYLocation));

	// De-project screen position of crosshair to the world direction
	FVector CrosshairWorldLocation;
	FVector CrosshairWorldDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CrosshairWorldLocation, CrosshairWorldDirection);

	// Line trace forward from that location, see what we hit
	FHitResult HitResult;
	float TraceRange = 1000000; // 10km or 1000000cm
	FVector TraceEnd = CrosshairWorldLocation + CrosshairWorldDirection * TraceRange;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetControlledTank());
	bool IsTargetInRange = GetWorld()->LineTraceSingleByChannel(HitResult, CrosshairWorldLocation, TraceEnd, ECC_Visibility, TraceParameters);
	DrawDebugLine(GetWorld(), HitResult.ImpactPoint, (HitResult.ImpactPoint + FVector(0.f, 0.f, 250.f)), FColor::Blue, false, 0.5f, NULL, 10.f); // Visual-aid for target point

	// Check to see if our trace collided with anything. Return the impact point and success accordingly
	if (IsTargetInRange)
	{
		HitLocation = HitResult.ImpactPoint;
		return true;
	}
	return false;
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}