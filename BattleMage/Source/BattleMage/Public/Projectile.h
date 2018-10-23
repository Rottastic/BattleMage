// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//Forward Declaration
class UProjectileMovementComponent;

UCLASS()
class BATTLEMAGE_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void LaunchProjectile(float LaunchSpeed);
};
