// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn them
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work out required acceleration to correct slippage
	auto CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	// Calculate required force to apply sideways acceleration
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();

	CurrentThrottle = 0.f;
}

void UTankTrack::SetThrottle(float Throttle)
{
	// Clamp Throttle to prevent exploits (should be -1, 1. But stops turning while forward)
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2, 2);
}
void UTankTrack::DriveTrack()
{
	// Force applied to the Tank root, at the location of the track
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}