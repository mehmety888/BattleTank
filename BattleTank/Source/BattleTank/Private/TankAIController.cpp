// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();  
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank))
        {
            return;
        }
        // subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}
void ATankAIController::OnPossessedTankDeath()
{
    if(!GetPawn())
    {
        return;
    }
    GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if(!(PlayerTank && ControlledTank))
    {
        return;
    }

    // TODO: Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent))
	{
		return;
	}
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    // Fire if ready
    if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
    {
        AimingComponent->Fire(); 
    }
    
}
