// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declaration
class UTankTrack;


/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLEMAGE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitialiseComponent(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Called from pathfinding logic, by AIController
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};