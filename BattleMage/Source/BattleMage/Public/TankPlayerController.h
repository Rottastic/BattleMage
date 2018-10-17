// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEMAGE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		ATank* GetControlledTank() const;

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;
		UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33333f;

		bool GetCrosshairHitLocation(FVector& OUT HitLocation) const;
		virtual void AimAtCrosshair();


};
