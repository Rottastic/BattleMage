// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPlayerController.generated.h"

// Forward Declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLEMAGE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
		UFUNCTION(BlueprintCallable)
		ATank* GetControlledTank() const;

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		UPROPERTY(EditDefaultsOnly)
			float CrosshairXLocation = 0.5f;
		UPROPERTY(EditDefaultsOnly)
			float CrosshairYLocation = 0.33333f;

		bool GetCrosshairHitLocation(FVector& OUT HitLocation) const;
		virtual void AimAtCrosshair();
};
