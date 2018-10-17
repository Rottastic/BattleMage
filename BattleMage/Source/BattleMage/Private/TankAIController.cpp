// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (ControlledTank && PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *GetDebugName(ControlledTank));
		UE_LOG(LogTemp, Warning, TEXT("%s is targeting %s"), *GetDebugName(ControlledTank), *GetDebugName(PlayerTank));
	}
	else if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *GetDebugName(ControlledTank));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is not possessing a Tank"));
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtPlayer();
}

void ATankAIController::AimAtPlayer()
{
	if (!GetControlledTank() || !GetPlayerTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		return Cast<ATank>(PlayerTank);
	}

	// If no PlayerTank is found, fail
	return nullptr;
}