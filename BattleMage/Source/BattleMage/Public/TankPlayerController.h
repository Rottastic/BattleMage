// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPlayerController.generated.h"

// Forward Declaration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLEMAGE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
		UFUNCTION(BlueprintCallable)
		APawn* GetControlledTank() const;

		UFUNCTION(BlueprintCallable)
		void SetSpectate();

		UFUNCTION(BlueprintImplementableEvent)
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		virtual void SetPawn(APawn* InPawn) override;
		UFUNCTION()
		void OnTankDeath();

		UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;
		UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333f;

		bool GetCrosshairHitLocation(FVector& OUT HitLocation) const;
		UTankAimingComponent* AimingComponent = nullptr;
		virtual void AimAtCrosshair();
};
