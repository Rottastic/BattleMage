// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declaration
class UTankAimingComponent;


/**
 * 
 */
UCLASS()
class BATTLEMAGE_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		// How close tank gets to target, before halting
		float AcceptanceRadius = 2500;

		APawn* ControlledTank = nullptr;
		APawn* PlayerTank = nullptr;
		UTankAimingComponent* AimingComponent = nullptr;
};
