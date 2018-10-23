// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;


UCLASS()
class BATTLEMAGE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();
	UPROPERTY(EditAnywhere)
	float ProjectileLaunchSpeed = 3000; // Unsure what value is best
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	bool IsFiring = false;

private:
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3.f;
	double LastFireTime = 0;
};
