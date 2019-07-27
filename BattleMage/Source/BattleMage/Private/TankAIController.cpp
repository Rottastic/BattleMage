// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding
#include "Tank.h"

#include "CoreMinimal.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerTank = nullptr;
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!(ControlledTank && PlayerTank)) { return; }

	// Move towards the Player
	MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);

	// Aim towards the Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire, if locked on Player
	if(AimingComponent->GetAimingState() == EAimingState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	ControlledTank->DetachFromControllerPendingDestroy();
}