// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankTurret.h"
#include "TankBarrel.h"

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::AimAt(FVector WorldLocation, float LaunchSpeed, bool DrawDebug)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity(0);
	bool IsHitPossible = GetTrajectory(OutLaunchVelocity, WorldLocation, LaunchSpeed, DrawDebug);
	if (DrawDebug) { Cast<ATank>(GetOwner())->IsFiring = false; }

	// Move the Tank&Barrel towards the target trajectory
	if (IsHitPossible)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(AimDirection);
	}
}
bool UTankAimingComponent::GetTrajectory(FVector &OutVelocity, FVector WorldLocation, float LaunchSpeed, bool DrawDebug)
{
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(Barrel->GetOwner());

	// Calculate the OutLaunchVelocity
	bool IsHitPossible = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutVelocity,
		StartLocation,
		WorldLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorToIgnore,
		DrawDebug
	);

	return IsHitPossible;
}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::MoveTurretAndBarrel(FVector AimDirection)
{
	// Figure out the difference between desired AimDirection and tank's current rotations
	auto AimAsRotator = AimDirection.Rotation();

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto DeltaTurretRotator = AimAsRotator - TurretRotation;
	Turret->Rotate(DeltaTurretRotator.Yaw);

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto DeltaBarrelRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaBarrelRotator.Pitch);
}