// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declaration
class UTankTrack;


/**
 * 
 */
UCLASS()
class BATTLEMAGE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void InitializeComponent(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);
	UFUNCTION(BlueprintCallable)
		void IntendMoveForward(float Throw);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;


};
