// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(!ensure(Barrel))
	{
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity 
							(
								this,
								OutLaunchVelocity,
								StartLocation,
								HitLocation,
								LaunchSpeed,
								false, // default, we can remove
								0, // default, we can remove
								0, // default, we can remove
								ESuggestProjVelocityTraceOption::DoNotTrace
							);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		// No aim solution found
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Barrel && Turret)) 
	{
		return;
	}
	// Workout difference between current barret rotation and aim direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

