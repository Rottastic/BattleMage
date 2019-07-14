// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLEMAGE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 20000000.f;

private:
	UTankTrack();
	virtual void BeginPlay() override;

	float CurrentThrottle = 0;

	void DriveTrack();
	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
