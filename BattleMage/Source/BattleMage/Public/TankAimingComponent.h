// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankTurret;
class UTankBarrel;
class AProjectile;


// Enum for aiming state
UENUM()
enum class EAimingState : uint8
{
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEMAGE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void InitialiseComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(FVector WorldLocation);
	bool GetTrajectory(FVector &OutVelocity, FVector WorldLocation, float LaunchSpeed, bool DrawDebug);
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	EAimingState AimingState = EAimingState::Aiming;
		
private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveTurretAndBarrel(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLaunchSpeed = 3000; // Unsure what value is best
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.f;
	double LastFireTime = 0;
	bool IsFiring = true;
};
