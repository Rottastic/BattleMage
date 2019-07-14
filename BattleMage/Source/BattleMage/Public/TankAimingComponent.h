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
	Reloading,
	OutOfAmmo
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

	UFUNCTION(BlueprintCallable)
	EAimingState GetAimingState() const;
	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() const;

protected:
	EAimingState AimingState = EAimingState::Reloading;
		
private:
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveTurretAndBarrel(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLaunchSpeed = 4000; // Unsure what value is best
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	int CurrentAmmo = 3;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.f;
	double LastFireTime = 0;
	bool IsBarrelMoving = false;
	bool IsReloaded = false;
	bool IsFiring = false;
};