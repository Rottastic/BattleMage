// Copyright Brenden Welch

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

// Forward Declarations
class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USphereComponent;


UCLASS()
class BATTLEMAGE_API ASprungWheel : public AActor
{
	GENERATED_BODY()

private:
	// Sets default values for this actor's properties
	ASprungWheel();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* SpringConstraint = nullptr;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* AxleMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* WheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* WheelMesh = nullptr;
};
