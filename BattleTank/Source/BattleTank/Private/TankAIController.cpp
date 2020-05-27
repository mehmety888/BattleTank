// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* PossessedTank = nullptr;
    PossessedTank  = GetAIControlledTank();

    if(PossessedTank == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("AIController not possessing a tank"));
    }
    else 
    {
        UE_LOG(LogTemp,Warning,TEXT("AIController possessing %s"),*PossessedTank->GetName());
    }    
}

ATank* ATankAIController::GetAIControlledTank() const
{
    return Cast<ATank>(GetPawn());
}