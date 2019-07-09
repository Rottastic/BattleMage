// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

void UTankAimingComponent::InitialiseComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


bool UTankAimingComponent::GetTrajectory(FVector &OutVelocity, FVector WorldLocation, float LaunchSpeed, bool DrawDebug)
{
	if (!ensure(Barrel)) { return nullptr; }
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
void UTankAimingComponent::AimAt(FVector WorldLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity(0);
	bool IsHitPossible = GetTrajectory(OutLaunchVelocity, WorldLocation, ProjectileLaunchSpeed, IsFiring);
	IsFiring = false; // Purely used to draw the debug line. Remove later

	// Move the Tank&Barrel towards the target trajectory
	if (IsHitPossible)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(AimDirection);
	}
	else
	{
		auto AimDirection = WorldLocation.GetSafeNormal();
		MoveTurretAndBarrel(AimDirection);
	}
}
void UTankAimingComponent::MoveTurretAndBarrel(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Figure out the difference between desired AimDirection and tank's current rotations
	auto AimAsRotator = AimDirection.Rotation();

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto DeltaTurretRotator = AimAsRotator - TurretRotation;
	Turret->Rotate(DeltaTurretRotator.Yaw);

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto DeltaBarrelRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaBarrelRotator.Pitch);
}
void UTankAimingComponent::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (IsReloaded)
	{
		if (!ensure(Barrel)) { return; }

		// Grab the angle of the barrel
		auto BarrelAimDirection = Barrel->GetComponentRotation().Vector();

		// Spawn a Projectile to launch
		auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		IsFiring = true;

		// Launch the Projectile according to Barrel's AimDirection
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}