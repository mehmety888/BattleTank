// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* PossessedTank = GetAIControlledTank();
    ATank* PlayerTank = GetPlayerTank();

    if(PossessedTank == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("AIController not possessing a tank"));
    }
    else 
    {
        UE_LOG(LogTemp,Warning,TEXT("AIController possessing %s"),*PossessedTank->GetName());
    }    

    if(PlayerTank == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("AIController cannot find player tank"));
    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("AIController find player tank named as %s"), *PlayerTank->GetName());
    }
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsPlayer();
}

ATank* ATankAIController::GetAIControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!PlayerPawn)
    {
        UE_LOG(LogTemp,Error,TEXT("Cannot find Player Controller"));
        return nullptr;
    }
    else 
    {
        return Cast<ATank>(PlayerPawn);
    }
}

void ATankAIController::AimTowardsPlayer()
{
    if(!GetAIControlledTank()||!GetPlayerTank())
    {
        return;
    }
    // TODO: Move towards the player

    // Aim towards the player
    FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
    GetAIControlledTank()->AimAt(PlayerLocation);
}