// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankTurret;
class UTankBarrel;


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

	void AimAt(FVector WorldLocation, float LaunchSpeed, bool DrawDebug);
	bool GetTrajectory(FVector &OutVelocity, FVector WorldLocation, float LaunchSpeed, bool DrawDebug);
	//void SetTurretReference(UTankTurret* TurretToSet);
	//void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UPROPERTY(BlueprintReadOnly)
	EAimingState AimingState = EAimingState::Aiming;
		
private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveTurretAndBarrel(FVector AimDirection);
};
