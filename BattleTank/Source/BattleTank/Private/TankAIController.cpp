// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();  
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ATank* PossessedTank = Cast<ATank>(GetPawn());
    if(!ensure(PossessedTank))
    {
        return;
    }

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(!ensure(PlayerTank))
    {
        UE_LOG(LogTemp,Error,TEXT("Cannot find Player Controller"));
        return;
    }

    // TODO: Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // Aim towards the player
    FVector PlayerLocation = PlayerTank->GetActorLocation();
    PossessedTank->AimAt(PlayerLocation);

    // Fire if ready
    PossessedTank->Fire(); // TODO: don't fire every frame
}
