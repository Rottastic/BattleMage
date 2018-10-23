// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankTurret;
class UTankBarrel;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEMAGE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldLocation, float LaunchSpeed, bool DrawDebug);
	bool GetTrajectory(FVector &OutVelocity, FVector WorldLocation, float LaunchSpeed, bool DrawDebug);
	void SetTurretReference(UTankTurret* TurretToSet);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
		
private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveTurretAndBarrel(FVector AimDirection);
};
