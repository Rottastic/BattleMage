// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Engine/World.h"
#include "CoreMinimal.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamageAmount = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamageAmount, 0, CurrentHealth);

	CurrentHealth = CurrentHealth - DamageToApply;

	AController* AffectedController = GetController();
	AController* PlayerController = GetWorld()->GetFirstPlayerController();
	if ((CurrentHealth <= 0) && !(AffectedController == PlayerController))
	{
		OnTankDeath.Broadcast();
		Destroy();
	}
	else if (CurrentHealth <= 0) // Save the player until death is implemented
	{
		OnTankDeath.Broadcast();
		Destroy();
		//CurrentHealth = MaxHealth;
		/*PlayerController->UnPossess();
		Destroy();
		
		Currently causes a crash. Likely because of UI and other dependencies on tank possession
		*/
	}

	return 0.f;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}