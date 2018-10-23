// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLEMAGE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward movement, +1 is max upward
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 30.f;

	//prevent self-collision
};
