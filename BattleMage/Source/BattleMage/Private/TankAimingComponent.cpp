// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn them
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start the game reloading, so that AI does not immediately fire
	LastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (CurrentAmmo < 1)
	{
		AimingState = EAimingState::OutOfAmmo;
	}
	else if (IsReloaded && !IsBarrelMoving)
	{
		AimingState = EAimingState::Locked;
	}
	else if (IsReloaded)
	{
		AimingState = EAimingState::Aiming;
	}
	else
	{
		AimingState = EAimingState::Reloading;
	}

}

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

	// Check to see if barrel is already aimed correctly
	if (OutLaunchVelocity.GetSafeNormal().Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.05f))
	{
		IsBarrelMoving = false;
	}
	else
	{
		IsBarrelMoving = true;
	}

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

	//FVector::Equals(OutLaunchVelocity.GetSafeNormal(), 30.f);

}
void UTankAimingComponent::MoveTurretAndBarrel(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Figure out the difference between desired AimDirection and tank's current rotations
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always choose the shortest rotation to aim
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}
void UTankAimingComponent::Fire()
{
	if (IsReloaded && !(AimingState == EAimingState::OutOfAmmo))
	{
		if (!ensure(Barrel)) { return; }

		// Grab the angle of the barrel
		auto BarrelAimDirection = Barrel->GetComponentRotation().Vector();

		// Spawn a Projectile to launch
		auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		IsFiring = false;

		// Launch the Projectile according to Barrel's AimDirection
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		CurrentAmmo--;
	}
}

EAimingState UTankAimingComponent::GetAimingState() const
{
	return AimingState;
}
int UTankAimingComponent::GetCurrentAmmo() const
{
	return CurrentAmmo;
}