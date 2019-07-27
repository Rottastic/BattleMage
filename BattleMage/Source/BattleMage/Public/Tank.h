// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLEMAGE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Returns current health as a percentage of max health, between 0 and 1
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	FTankDelegate OnTankDeath;

private:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth = 0;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};