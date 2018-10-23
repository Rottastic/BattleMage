// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"
#include "CoreMinimal.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector TargetLocation)
{
	TankAimingComponent->AimAt(TargetLocation, ProjectileLaunchSpeed, IsFiring);
}
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	TankAimingComponent->SetTurretReference(TurretToSet);
}
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (IsReloaded)
	{
		auto BarrelComponent = FindComponentByClass<UTankBarrel>();
		auto BarrelAimDirection = BarrelComponent->GetComponentRotation().Vector();

		// Spawn a Projectile to launch
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		IsFiring = true;

		// Launch the Projectile according to Barrel's AimDirection
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}