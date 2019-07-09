// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

#include "CoreMinimal.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ControlledTank && PlayerTank)
	{
		// Aim towards the Player
		//ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//ControlledTank->Fire();

		// Move towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);
	}
}