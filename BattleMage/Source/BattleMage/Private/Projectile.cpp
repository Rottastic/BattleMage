// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "Engine/World.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

#include "CoreMinimal.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetWorldScale3D(FVector(0.5f));
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force Component"));
	ExplosionForce->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	// A little magic to launch a bouncing projectile
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->Velocity = GetActorRotation().Vector().GetSafeNormal() * LaunchSpeed;
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	// Impact explosion effect begins, trail effect ends
	ImpactBlast->Activate();
	LaunchBlast->Deactivate();
	// Explosion force is applied around the impact
	ExplosionForce->FireImpulse();
	// Projectile is "destroyed"
	CollisionMesh->SetVisibility(false);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// After a delay, currently: 3sec, entire projectile is deleted
	FTimerHandle DeathTimer;
	GetWorldTimerManager().SetTimer(DeathTimer, [this]() {Destroy();}, 1.f, false, DeathTimerDelay);
}