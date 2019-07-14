// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding

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

	if (!ensure(ControlledTank && PlayerTank)) { return; }

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