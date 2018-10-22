// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declaration
class ATank;


/**
 * 
 */
UCLASS()
class BATTLEMAGE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		ATank* GetControlledTank() const;

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		ATank* GetPlayerTank() const;
		virtual void AimAtPlayer();
};
