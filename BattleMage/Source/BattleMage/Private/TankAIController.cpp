// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding

#include "CoreMinimal.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(ControlledTank && PlayerTank)) { return; }

		// Aim towards the Player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();

		// Move towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);
}