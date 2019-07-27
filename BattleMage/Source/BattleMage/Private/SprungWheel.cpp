// Copyright Brenden Welch

#include "SprungWheel.h"

#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/SphereComponent.h"


ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component structure and some default values
	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SetRootComponent(SpringConstraint);

	AxleMesh = CreateDefaultSubobject<USphereComponent>(FName("AxleMesh"));
	AxleMesh->AttachToComponent(SpringConstraint, FAttachmentTransformRules::KeepRelativeTransform);

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->AttachToComponent(AxleMesh, FAttachmentTransformRules::KeepRelativeTransform);

	WheelMesh = CreateDefaultSubobject<USphereComponent>(FName("WheelMesh"));
	WheelMesh->AttachToComponent(WheelConstraint, FAttachmentTransformRules::KeepRelativeTransform);
}
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, AxleMesh, NAME_None);
	WheelConstraint->SetConstrainedComponents(AxleMesh, NAME_None, WheelMesh, NAME_None);
}
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

