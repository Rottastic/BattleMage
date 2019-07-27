// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//Forward Declaration
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLEMAGE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:	
	void LaunchProjectile(float LaunchSpeed);

protected:
	// Core projectile components
	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* CollisionMesh = nullptr;

private:
	// Sets default values for this actor's properties
	AProjectile();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Core projectile components
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	// Particle systems
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DeathTimerDelay = 3.f;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileDamage = 10.f;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
